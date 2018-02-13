namespace DummyClient
{
    partial class LoginForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textbox_id_ = new System.Windows.Forms.TextBox();
            this.textbox_pw_ = new System.Windows.Forms.TextBox();
            this.button_login_ = new System.Windows.Forms.Button();
            this.button_quit_ = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // textbox_id_
            // 
            this.textbox_id_.Location = new System.Drawing.Point(78, 25);
            this.textbox_id_.Name = "textbox_id_";
            this.textbox_id_.Size = new System.Drawing.Size(109, 21);
            this.textbox_id_.TabIndex = 0;
            // 
            // textbox_pw_
            // 
            this.textbox_pw_.Location = new System.Drawing.Point(78, 52);
            this.textbox_pw_.Name = "textbox_pw_";
            this.textbox_pw_.Size = new System.Drawing.Size(109, 21);
            this.textbox_pw_.TabIndex = 1;
            // 
            // button_login_
            // 
            this.button_login_.Location = new System.Drawing.Point(12, 91);
            this.button_login_.Name = "button_login_";
            this.button_login_.Size = new System.Drawing.Size(75, 23);
            this.button_login_.TabIndex = 2;
            this.button_login_.Text = "로그인";
            this.button_login_.UseVisualStyleBackColor = true;
            this.button_login_.Click += new System.EventHandler(this.button_login__Click);
            // 
            // button_quit_
            // 
            this.button_quit_.Location = new System.Drawing.Point(107, 91);
            this.button_quit_.Name = "button_quit_";
            this.button_quit_.Size = new System.Drawing.Size(75, 23);
            this.button_quit_.TabIndex = 3;
            this.button_quit_.Text = "종료";
            this.button_quit_.UseVisualStyleBackColor = true;
            this.button_quit_.Click += new System.EventHandler(this.button_quit__Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(33, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(16, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "ID";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 12);
            this.label2.TabIndex = 5;
            this.label2.Text = "Password";
            // 
            // LoginForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(197, 126);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_quit_);
            this.Controls.Add(this.button_login_);
            this.Controls.Add(this.textbox_pw_);
            this.Controls.Add(this.textbox_id_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "LoginForm";
            this.Text = "DummyLogin";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textbox_id_;
        private System.Windows.Forms.TextBox textbox_pw_;
        private System.Windows.Forms.Button button_login_;
        private System.Windows.Forms.Button button_quit_;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}