namespace DummyClient
{
    partial class ChattingForm
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
            this.richTextBox_view_ = new System.Windows.Forms.RichTextBox();
            this.textbox_input_ = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // richTextBox_view_
            // 
            this.richTextBox_view_.BackColor = System.Drawing.Color.Teal;
            this.richTextBox_view_.ForeColor = System.Drawing.Color.White;
            this.richTextBox_view_.Location = new System.Drawing.Point(20, 12);
            this.richTextBox_view_.Name = "richTextBox_view_";
            this.richTextBox_view_.ReadOnly = true;
            this.richTextBox_view_.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.richTextBox_view_.Size = new System.Drawing.Size(455, 295);
            this.richTextBox_view_.TabIndex = 0;
            this.richTextBox_view_.Text = "";
            // 
            // textbox_input_
            // 
            this.textbox_input_.Location = new System.Drawing.Point(20, 315);
            this.textbox_input_.Name = "textbox_input_";
            this.textbox_input_.Size = new System.Drawing.Size(455, 21);
            this.textbox_input_.TabIndex = 1;
            this.textbox_input_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textbox_input_KeyDown);
            // 
            // ChattingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(500, 350);
            this.Controls.Add(this.textbox_input_);
            this.Controls.Add(this.richTextBox_view_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "ChattingForm";
            this.Text = "ChattingForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBox_view_;
        private System.Windows.Forms.TextBox textbox_input_;
    }
}