#pragma once


namespace �������� {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace System::Text::RegularExpressions;

	/// <summary>
	/// Form1 ժҪ
	///
	/// ����: ������Ĵ�������ƣ�����Ҫ����
	///          ����������������� .resx �ļ��������й���Դ���������ߵ�
	///          ����Դ�ļ��������ԡ�����
	///          �������������˴���Ĺ���
	///          ���ػ���Դ��ȷ������
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
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
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
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

			  void sworm(string filename)//�ӱ����ļ���ʼ��
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
			Regex pattern("href=[^.]+.html");	//ƥ��������ʽ
			
			//if(pattern.IsMatch(Input))//?"1":"0";
			{//String^ Text=
				
			}
			
		}
		//while(IsMatch(
		
	//string format
	}

	};


}

