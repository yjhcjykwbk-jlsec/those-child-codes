#pragma once


namespace 本地爬虫 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace System::Text::RegularExpressions;

	/// <summary>
	/// Form1 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(67, 35);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(151, 21);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				// string url=this.Text;
				// GraphL newgra;
				 //treeSearch(url);
				 //textBox1->Text="saadashd";
				
				 

			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {textBox1->Text="llll1";
				 sworm("g:\\index.html");
			 }

			  void sworm(string filename)//从本地文件开始爬
	{
		//,GraphL &a
		ifstream reader(filename.c_str(),ios::in);
		char* buffer=new char[2048];
		if(!reader)
		{
			cerr<<"error";
		}
		while(!reader.eof())
		{
			string Input="<link href=images/index/login.html rel=stylesheet type=text/css />";//"/<a href=*/>";
			//Input=buffer;
			reader.getline(buffer,1024);
			String^ end(buffer);
			//String^ patternRegex::IsMatch
			Regex pattern("href=[^.]+.html");	//匹配正则表达式
			
			//if(pattern.IsMatch(Input))//?"1":"0";
			{//String^ Text=
				
			}
			
		}
		//while(IsMatch(
		
	//string format
	}

	};


}

