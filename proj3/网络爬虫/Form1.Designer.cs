namespace 搜索引擎
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.originalWebFile = new System.Windows.Forms.TextBox();
            this.start = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.stopDownload = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // originalWebFile
            // 
            this.originalWebFile.Location = new System.Drawing.Point(37, 26);
            this.originalWebFile.Name = "originalWebFile";
            this.originalWebFile.Size = new System.Drawing.Size(334, 21);
            this.originalWebFile.TabIndex = 3;
            this.originalWebFile.Text = "输入网址(默认http://www.pku.edu.cn)";
            this.originalWebFile.TextChanged += new System.EventHandler(this.originalWebFile_TextChanged);
            // 
            // start
            // 
            this.start.Location = new System.Drawing.Point(267, 127);
            this.start.Name = "start";
            this.start.Size = new System.Drawing.Size(75, 23);
            this.start.TabIndex = 5;
            this.start.Text = "开始";
            this.start.UseVisualStyleBackColor = true;
            this.start.Click += new System.EventHandler(this.start_Click);
            // 
            // stopDownload
            // 
            this.stopDownload.Location = new System.Drawing.Point(88, 127);
            this.stopDownload.Name = "stopDownload";
            this.stopDownload.Size = new System.Drawing.Size(75, 23);
            this.stopDownload.TabIndex = 9;
            this.stopDownload.Text = "停止";
            this.stopDownload.UseVisualStyleBackColor = true;
            this.stopDownload.Click += new System.EventHandler(this.stopDownload_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(531, 363);
            this.Controls.Add(this.stopDownload);
            this.Controls.Add(this.start);
            this.Controls.Add(this.originalWebFile);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox originalWebFile;
        private System.Windows.Forms.Button start;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Button stopDownload;
    }
}

