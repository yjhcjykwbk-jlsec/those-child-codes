namespace searchEngines
{
    partial class searchEngines
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
            this.buttonSearch = new System.Windows.Forms.Button();
            this.searchStr = new System.Windows.Forms.TextBox();
            this.buttonMakeIndexTable = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonSearch
            // 
            this.buttonSearch.Location = new System.Drawing.Point(318, 270);
            this.buttonSearch.Name = "buttonSearch";
            this.buttonSearch.Size = new System.Drawing.Size(75, 23);
            this.buttonSearch.TabIndex = 0;
            this.buttonSearch.Text = "百度一下";
            this.buttonSearch.UseVisualStyleBackColor = true;
            this.buttonSearch.Click += new System.EventHandler(this.buttonSearch_Click);
            // 
            // searchStr
            // 
            this.searchStr.Location = new System.Drawing.Point(86, 226);
            this.searchStr.Name = "searchStr";
            this.searchStr.Size = new System.Drawing.Size(327, 21);
            this.searchStr.TabIndex = 1;
            this.searchStr.TextChanged += new System.EventHandler(this.searchStr_TextChanged);
            // 
            // buttonMakeIndexTable
            // 
            this.buttonMakeIndexTable.Location = new System.Drawing.Point(123, 270);
            this.buttonMakeIndexTable.Name = "buttonMakeIndexTable";
            this.buttonMakeIndexTable.Size = new System.Drawing.Size(75, 23);
            this.buttonMakeIndexTable.TabIndex = 2;
            this.buttonMakeIndexTable.Text = "建表";
            this.buttonMakeIndexTable.UseVisualStyleBackColor = true;
            this.buttonMakeIndexTable.Click += new System.EventHandler(this.buttonMakeIndexTable_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::searchEngines.Properties.Resources.op_logo;
            this.pictureBox1.Location = new System.Drawing.Point(123, 53);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(270, 132);
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            // 
            // searchEngines
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(515, 327);
            this.Controls.Add(this.buttonSearch);
            this.Controls.Add(this.buttonMakeIndexTable);
            this.Controls.Add(this.searchStr);
            this.Controls.Add(this.pictureBox1);
            this.Name = "searchEngines";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonSearch;
        private System.Windows.Forms.TextBox searchStr;
        private System.Windows.Forms.Button buttonMakeIndexTable;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

