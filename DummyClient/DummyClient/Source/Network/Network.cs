using System;
using System.IO;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;

namespace DummyClient
{
    internal enum NET_STATE
    {
        START,
        CONNECTED,
        DISCONNECT,
        DISCONNECTED,
    }

    internal class Network
    {
        private NetworkStream stream_;

        private Thread readWorker_;
        private Thread hearBeatWorker_;

        private TcpClient client_;
        private NET_STATE state_ = NET_STATE.START;

        private PacketProcess packetProcee_;
        
        ~Network()
        {
            if (this.isConnected()) {
                this.disConnect();
            }
        }

        NET_STATE state()
        {
            return state_;
        }

        public void close()
        {
            state_ = NET_STATE.DISCONNECTED;
            stream_.Close();
            stream_.Flush();
            stream_.Close();
            readWorker_.Abort();
            hearBeatWorker_.Abort();
            packetProcee_ = null;
        }

        public bool connect(string ip, int port)
        {
            client_ = new TcpClient();
            try {
                client_.Connect(ip, port);
            }
            catch {
                MessageBox.Show("서버 연결 실패", "error", MessageBoxButtons.OK);
                return false;
            }
            state_ = NET_STATE.CONNECTED;

            stream_ = client_.GetStream();

            readWorker_ = new Thread(new ThreadStart(receive));
            readWorker_.Start();

            hearBeatWorker_ = new Thread(new ThreadStart(hearBeat));
            hearBeatWorker_.Start();
            return true;
        }

        public void disConnect()
        {
            state_ = NET_STATE.DISCONNECT;
            PK_C_REQ_EXIT packet = new PK_C_REQ_EXIT();
            this.sendPacket(packet);
        }

        public void setPacketProcess(PacketProcess packetProcess)
        {
            packetProcee_ = packetProcess;
        }

        private bool isConnected()
        {
            try {
                while (this.isConnected) {
                    Byte[] packetByte = new Byte[client_.ReceiveBufferSize];

                    Int32 offset = 0;
                    Int32 readLen = stream_.Read(packetByte, offset, packetByte.Length);
                    Int32 packetLen = PacketUtil.decodePacketLen(packetByte, ref offset);
                    while (readLen < packetLen) {
                        Byte[] remainPacket = new Byte[client_.ReceiveBufferSize];
                        Int32 remainLen = 0;
                        remainLen = stream_.Read(remainPacket, 0, remainPacket.Length);
                        Buffer.BlockCopy(remainPacket, 0, packetByte, readLen, remainLen);
                        readLen += remainLen;
                    }

                    PacketInterface rowPacket = PacketUtil.packetAnalyzer(packetByte, ref offset, readLen);

                    if (rowPacket == null && this.isConnected()) {
                        MessageBox("잘못된 패킷이 수신되었습니다", "error", MessageBoxButtons.OK);
                        Application.Exit();
                    }
                    packetProcee_.run(rowPacket);
                }
                this.close();
            }
            catch (Exception e) {
                if (this.isConnected()) {
                    MessageBox("잘못된 처리 : " + e.ToString(), "error", MessageBoxButtons.OK);
                    Application.Exit();
                }
            }
        }

        public void sendPacket(PacketInterface packet)
        {
            try {
                packet.encode();
                MemoryStream packetData = new MemoryStream();

                Int32 packetLen = sizeof(Int32) + (Int32)packet.getStream().Length;

                packetData.Write(BitConverter.GetBytes(packetLen), 0, sizeof(Int32));
                packetData.Write(packet.getStream().ToArray(), 0, (Int32)packet.getStream().Length);

                Byte[] packetBytes = packetData.ToArray();
                stream_.Write(packetBytes, 0, (int)packetData.Length);
                stream_.Flush();

                packetData = null;
            }
            catch (Exception e) {
                if (this.isConnected()) {
                    MessageBox.Show("잘못된 처리 : " + e.ToString(), "error", MessageBoxButtons.OK);
                    Application.Exit();
                }
            }
        }

        private void hearBeat()
        {
            while (this.isConnected) {
                PK_C_NOTIFY_HEARTBEAT hearBeatPacket = new PK_C_NOTIFY_HEARTBEAT();
                this.sendPacket(hearBeatPacket);
                Thread.Sleep(1000);
            }
        }
    }

}
