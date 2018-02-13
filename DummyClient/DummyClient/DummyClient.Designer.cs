namespace DummyClient
{
    partial class DummyClient
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainPanel_ = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // mainPanel_
            // 
            this.mainPanel_.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainPanel_.Location = new System.Drawing.Point(0, 0);
            this.mainPanel_.Name = "mainPanel_";
            this.mainPanel_.Size = new System.Drawing.Size(624, 441);
            this.mainPanel_.TabIndex = 0;
            // 
            // DummyClient
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(624, 441);
            this.Controls.Add(this.mainPanel_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "DummyClient";
            this.Text = "DummyClient";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.DummyClient_FormClosed);
            this.Shown += new System.EventHandler(this.DummyClient_Shown);
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.Panel mainPanel_;
    }
}

