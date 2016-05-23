/*
3-clause BSD license

Copyright (c) 2014-2016 Michael Krause (krause@tum.de) Institute of Ergonomics, Technische Universität München

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include <windows.h> 
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <stdio.h> 
#include <wchar.h> 
#include <string.h> 
#include <winnls.h>
#include <vcclr.h> // required header for PtrToStringChars
#include <msclr/marshal.h> 
#include <msclr\marshal_cppstd.h> 


#pragma unmanaged
	typedef void (__cdecl *MCB)(int, int, int, int, void*);//MouseCallBack

	typedef struct{
			int p[8];
	}  ints;

#pragma managed


namespace show {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace msclr::interop; 
	using namespace System::Runtime::InteropServices;//alloc
	using namespace System::Configuration;// setting reader 
	using namespace System::Threading;


	/// <summary>
	/// Zusammenfassung für Form1
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie auch
	///          die Ressourcendateiname-Eigenschaft für das Tool zur Kompilierung verwalteter Ressourcen ändern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abhängt.
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate void mouseCallbackDelegate(int, int, int, int, void*);
	public:
	mouseCallbackDelegate^ fp;
	GCHandle gch;
	IntPtr ip;
	private: System::Windows::Forms::Button^  matchB;
	private: System::Windows::Forms::Label^  thresholdInfoLabel;
	public: 

	private: System::Windows::Forms::Button^  saveButton;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  infoLabel;
	private: System::Windows::Forms::ComboBox^  markerComboBox;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Button^  folderButton;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::Label^  folderLabel;
	private: System::Windows::Forms::Button^  aboutButton;
	private: System::Windows::Forms::Label^  batchProgressLabel;
	private: System::Windows::Forms::Panel^  batchPanel;
	private: System::Windows::Forms::Label^  batchLabel;
	private: System::Windows::Forms::Button^  batchButton;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  navInfoLabel;
	private: System::Windows::Forms::Label^  adhusThresholdLabel2;
	public: static CvMouseCallback mcb;

	public:	Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//

			//open openCV windows
			cvNamedWindow("frameWin", CV_WINDOW_AUTOSIZE);

			fp = gcnew mouseCallbackDelegate(&show::Form1::myMouseHandler);
			//fp->Invoke(0,0,0,0,NULL);

		    gch = GCHandle::Alloc(fp);
		    ip = Marshal::GetFunctionPointerForDelegate(fp);
		    //pin_ptr<mouseCallbackDelegate^> pp;

		    mcb = static_cast<MCB>(ip.ToPointer());
			cvSetMouseCallback("frameWin", mcb, NULL);

			cvNamedWindow("template", CV_WINDOW_AUTOSIZE);

		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}

		 try{ 
			//release resources
			 if(capture1){
				 pin_ptr<CvCapture*> p;
				 p = &capture1;
				 cvReleaseCapture( p ); 
			 }
			//cvReleaseCapture(&capture2);
			cvDestroyWindow( "frameWin" );

			cvDestroyWindow( "template" );

			if(mouseImg){
				pin_ptr<IplImage*> p;
				p = &mouseImg;
				cvReleaseImage(p);
			}
			if(resultImg){
				pin_ptr<IplImage*> p;
				p = &resultImg;
				cvReleaseImage(p);
			}
			if(templateImg1){
				pin_ptr<IplImage*> p;
				p = &templateImg1;
				cvReleaseImage(p);
			}

			

		 }
		 catch(...){ 
			 //openCVmsgDelegate(" failed to release ressources" );
		 }
		}
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	protected: 
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  openB;
	private: System::Windows::Forms::Label^  fileLabel;
	private: System::Windows::Forms::TextBox^  openCVstatus;
	private: System::Windows::Forms::Label^  messageLabel;

	private: System::Windows::Forms::Label^  frameLabel;

	private: System::Windows::Forms::Button^  nextB;
	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openB = (gcnew System::Windows::Forms::Button());
			this->fileLabel = (gcnew System::Windows::Forms::Label());
			this->openCVstatus = (gcnew System::Windows::Forms::TextBox());
			this->messageLabel = (gcnew System::Windows::Forms::Label());
			this->frameLabel = (gcnew System::Windows::Forms::Label());
			this->nextB = (gcnew System::Windows::Forms::Button());
			this->matchB = (gcnew System::Windows::Forms::Button());
			this->thresholdInfoLabel = (gcnew System::Windows::Forms::Label());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->navInfoLabel = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->adhusThresholdLabel2 = (gcnew System::Windows::Forms::Label());
			this->infoLabel = (gcnew System::Windows::Forms::Label());
			this->markerComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->batchPanel = (gcnew System::Windows::Forms::Panel());
			this->batchProgressLabel = (gcnew System::Windows::Forms::Label());
			this->folderLabel = (gcnew System::Windows::Forms::Label());
			this->batchLabel = (gcnew System::Windows::Forms::Label());
			this->folderButton = (gcnew System::Windows::Forms::Button());
			this->batchButton = (gcnew System::Windows::Forms::Button());
			this->aboutButton = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->panel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			this->batchPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToOrderColumns = true;
			this->dataGridView1->ClipboardCopyMode = System::Windows::Forms::DataGridViewClipboardCopyMode::EnableWithoutHeaderText;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
			this->dataGridView1->Location = System::Drawing::Point(12, 12);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(803, 218);
			this->dataGridView1->TabIndex = 0;
			this->dataGridView1->CellEnter += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView1_CellEnter);
			this->dataGridView1->RowStateChanged += gcnew System::Windows::Forms::DataGridViewRowStateChangedEventHandler(this, &Form1::dataGridView1_RowStateChanged);
			this->dataGridView1->Enter += gcnew System::EventHandler(this, &Form1::dataGridView1_Enter);
			// 
			// openB
			// 
			this->openB->Location = System::Drawing::Point(6, 28);
			this->openB->Name = L"openB";
			this->openB->Size = System::Drawing::Size(111, 23);
			this->openB->TabIndex = 1;
			this->openB->Text = L"1. open field video";
			this->openB->UseVisualStyleBackColor = true;
			this->openB->Click += gcnew System::EventHandler(this, &Form1::openB_Click);
			// 
			// fileLabel
			// 
			this->fileLabel->AutoSize = true;
			this->fileLabel->Location = System::Drawing::Point(10, 16);
			this->fileLabel->Name = L"fileLabel";
			this->fileLabel->Size = System::Drawing::Size(16, 13);
			this->fileLabel->TabIndex = 2;
			this->fileLabel->Text = L"---";
			// 
			// openCVstatus
			// 
			this->openCVstatus->Location = System::Drawing::Point(8, 68);
			this->openCVstatus->Multiline = true;
			this->openCVstatus->Name = L"openCVstatus";
			this->openCVstatus->ReadOnly = true;
			this->openCVstatus->Size = System::Drawing::Size(420, 71);
			this->openCVstatus->TabIndex = 3;
			// 
			// messageLabel
			// 
			this->messageLabel->AutoSize = true;
			this->messageLabel->Location = System::Drawing::Point(5, 59);
			this->messageLabel->Name = L"messageLabel";
			this->messageLabel->Size = System::Drawing::Size(35, 13);
			this->messageLabel->TabIndex = 2;
			this->messageLabel->Text = L"status";
			// 
			// frameLabel
			// 
			this->frameLabel->AutoSize = true;
			this->frameLabel->Location = System::Drawing::Point(436, 68);
			this->frameLabel->Name = L"frameLabel";
			this->frameLabel->Size = System::Drawing::Size(36, 13);
			this->frameLabel->TabIndex = 2;
			this->frameLabel->Text = L"frame:";
			// 
			// nextB
			// 
			this->nextB->Location = System::Drawing::Point(433, 83);
			this->nextB->Name = L"nextB";
			this->nextB->Size = System::Drawing::Size(73, 37);
			this->nextB->TabIndex = 5;
			this->nextB->Text = L"show next frame >";
			this->nextB->UseVisualStyleBackColor = true;
			this->nextB->Click += gcnew System::EventHandler(this, &Form1::nextB_Click);
			// 
			// matchB
			// 
			this->matchB->Location = System::Drawing::Point(347, 28);
			this->matchB->Name = L"matchB";
			this->matchB->Size = System::Drawing::Size(117, 23);
			this->matchB->TabIndex = 7;
			this->matchB->Text = L"3. template matching";
			this->matchB->UseVisualStyleBackColor = true;
			this->matchB->Click += gcnew System::EventHandler(this, &Form1::match_Click);
			// 
			// thresholdInfoLabel
			// 
			this->thresholdInfoLabel->AutoSize = true;
			this->thresholdInfoLabel->Location = System::Drawing::Point(478, 9);
			this->thresholdInfoLabel->Name = L"thresholdInfoLabel";
			this->thresholdInfoLabel->Size = System::Drawing::Size(150, 13);
			this->thresholdInfoLabel->TabIndex = 2;
			this->thresholdInfoLabel->Text = L"4. adjust templateFit threshold:";
			// 
			// saveButton
			// 
			this->saveButton->Location = System::Drawing::Point(653, 11);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(121, 23);
			this->saveButton->TabIndex = 7;
			this->saveButton->Text = L"5. save markerfile";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &Form1::saveButton_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->navInfoLabel);
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Controls->Add(this->messageLabel);
			this->panel1->Controls->Add(this->openCVstatus);
			this->panel1->Controls->Add(this->frameLabel);
			this->panel1->Controls->Add(this->nextB);
			this->panel1->Controls->Add(this->batchPanel);
			this->panel1->Location = System::Drawing::Point(12, 236);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(789, 193);
			this->panel1->TabIndex = 13;
			// 
			// navInfoLabel
			// 
			this->navInfoLabel->AutoSize = true;
			this->navInfoLabel->Location = System::Drawing::Point(435, 122);
			this->navInfoLabel->Name = L"navInfoLabel";
			this->navInfoLabel->Size = System::Drawing::Size(356, 13);
			this->navInfoLabel->TabIndex = 23;
			this->navInfoLabel->Text = L"You can also use up/down arrow and page up/down when grid has focus";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->adhusThresholdLabel2);
			this->groupBox1->Controls->Add(this->infoLabel);
			this->groupBox1->Controls->Add(this->markerComboBox);
			this->groupBox1->Controls->Add(this->numericUpDown1);
			this->groupBox1->Controls->Add(this->fileLabel);
			this->groupBox1->Controls->Add(this->saveButton);
			this->groupBox1->Controls->Add(this->matchB);
			this->groupBox1->Controls->Add(this->openB);
			this->groupBox1->Controls->Add(this->thresholdInfoLabel);
			this->groupBox1->Location = System::Drawing::Point(2, 0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(779, 61);
			this->groupBox1->TabIndex = 22;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"work flow";
			// 
			// adhusThresholdLabel2
			// 
			this->adhusThresholdLabel2->AutoSize = true;
			this->adhusThresholdLabel2->Location = System::Drawing::Point(490, 21);
			this->adhusThresholdLabel2->Name = L"adhusThresholdLabel2";
			this->adhusThresholdLabel2->Size = System::Drawing::Size(146, 13);
			this->adhusThresholdLabel2->TabIndex = 17;
			this->adhusThresholdLabel2->Text = L"(a low fit value means \'better\')";
			// 
			// infoLabel
			// 
			this->infoLabel->AutoSize = true;
			this->infoLabel->Location = System::Drawing::Point(135, 33);
			this->infoLabel->Name = L"infoLabel";
			this->infoLabel->Size = System::Drawing::Size(206, 13);
			this->infoLabel->TabIndex = 13;
			this->infoLabel->Text = L"2. Select template within \'frameWin\' (draw)";
			// 
			// markerComboBox
			// 
			this->markerComboBox->FormattingEnabled = true;
			this->markerComboBox->Location = System::Drawing::Point(653, 36);
			this->markerComboBox->Name = L"markerComboBox";
			this->markerComboBox->Size = System::Drawing::Size(121, 21);
			this->markerComboBox->TabIndex = 15;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(493, 36);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {7000, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(59, 20);
			this->numericUpDown1->TabIndex = 16;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {450, 0, 0, 0});
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// batchPanel
			// 
			this->batchPanel->BackColor = System::Drawing::SystemColors::Control;
			this->batchPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->batchPanel->Controls->Add(this->batchProgressLabel);
			this->batchPanel->Controls->Add(this->folderLabel);
			this->batchPanel->Controls->Add(this->batchLabel);
			this->batchPanel->Controls->Add(this->folderButton);
			this->batchPanel->Controls->Add(this->batchButton);
			this->batchPanel->Location = System::Drawing::Point(9, 141);
			this->batchPanel->Name = L"batchPanel";
			this->batchPanel->Size = System::Drawing::Size(766, 41);
			this->batchPanel->TabIndex = 21;
			// 
			// batchProgressLabel
			// 
			this->batchProgressLabel->AutoSize = true;
			this->batchProgressLabel->Location = System::Drawing::Point(10, 21);
			this->batchProgressLabel->Name = L"batchProgressLabel";
			this->batchProgressLabel->Size = System::Drawing::Size(16, 13);
			this->batchProgressLabel->TabIndex = 14;
			this->batchProgressLabel->Text = L"---";
			// 
			// folderLabel
			// 
			this->folderLabel->AutoSize = true;
			this->folderLabel->Location = System::Drawing::Point(369, 18);
			this->folderLabel->Name = L"folderLabel";
			this->folderLabel->Size = System::Drawing::Size(163, 13);
			this->folderLabel->TabIndex = 18;
			this->folderLabel->Text = L"select folder for batch processing";
			this->folderLabel->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// batchLabel
			// 
			this->batchLabel->AutoSize = true;
			this->batchLabel->Location = System::Drawing::Point(0, -1);
			this->batchLabel->Name = L"batchLabel";
			this->batchLabel->Size = System::Drawing::Size(236, 13);
			this->batchLabel->TabIndex = 22;
			this->batchLabel->Text = L"batch (apply settings above to a complete folder)";
			// 
			// folderButton
			// 
			this->folderButton->Location = System::Drawing::Point(344, 13);
			this->folderButton->Name = L"folderButton";
			this->folderButton->Size = System::Drawing::Size(25, 23);
			this->folderButton->TabIndex = 17;
			this->folderButton->Text = L"...";
			this->folderButton->UseVisualStyleBackColor = true;
			this->folderButton->Click += gcnew System::EventHandler(this, &Form1::folderButton_Click);
			// 
			// batchButton
			// 
			this->batchButton->Location = System::Drawing::Point(131, 14);
			this->batchButton->Name = L"batchButton";
			this->batchButton->Size = System::Drawing::Size(188, 23);
			this->batchButton->TabIndex = 19;
			this->batchButton->Text = L"start batch processing";
			this->batchButton->UseVisualStyleBackColor = true;
			this->batchButton->Click += gcnew System::EventHandler(this, &Form1::batchButton_Click);
			// 
			// aboutButton
			// 
			this->aboutButton->Location = System::Drawing::Point(800, 409);
			this->aboutButton->Name = L"aboutButton";
			this->aboutButton->Size = System::Drawing::Size(25, 23);
			this->aboutButton->TabIndex = 20;
			this->aboutButton->Text = L"\?";
			this->aboutButton->UseVisualStyleBackColor = true;
			this->aboutButton->Click += gcnew System::EventHandler(this, &Form1::aboutButton_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(825, 433);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->aboutButton);
			this->Controls->Add(this->dataGridView1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"Form1";
			this->Text = L"marker 1.5";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->batchPanel->ResumeLayout(false);
			this->batchPanel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


	static IplImage* resultImg;//result image for templateMatching function
	static IplImage* templateImg1;//template for template matching. 
	
	array<String^>^ filePaths; // array of file names for batch processing
	static int filePathsIndex; //current index of batch processed file
	System::Boolean batch;//true if batch process is running
	

	static CvCapture* capture1;
	static IplImage *frame1;//current frame captured from capture1, DONT free
	static int currentFrame;
	System::Boolean static matching;//true if template matching is in progress

	System::Boolean loading;//true if csv is actually loading


	static IplImage* mouseImg;//used in mouseHandler
	int static ddx,ddy;
	int static drag;


	#define MSG_SELECT_ROW 1
	#define MSG_PROGRESS 2
	#define MSG_FORM_OFF 3
	#define MSG_FORM_ON 4
	#define MSG_DONE 5
	#define MSG_SHOW_CURRENT_FRAME 6
		 

	private: System::Void open(System::String^ fn){
				 msgCallback(MSG_FORM_OFF, 0);//enable some user interaction with form

				 loading = true;
				 int count = 0;
				 fileLabel->Text = fn ;
				 openCVstatus->Text = "";
					

				 dataGridView1->Rows->Clear();
				 dataGridView1->Columns->Clear();
				 dataGridView1->Rows->Clear();

				System::String^ videofileName = fn;

				 //if this is the second field cam video open the first one to get the offset for counting frame
				/*
				if(videofileName->Contains("0001.avi")){
					secondVideo = true;

					System::String^ tempFileName = videofileName->Replace("-0001.avi","-0000.avi");
				    openCVstatus->AppendText("Try to open first video to get frameoffset: " +tempFileName + "\r\n");

					 const char* filename1 = (char*)(void*)Marshal::StringToHGlobalAnsi(tempFileName);
					 if (!(capture1 = cvCreateFileCapture(filename1))){
						 openCVstatus->AppendText("Error opening: " +tempFileName+ "\r\n");
					 }else{
						secondVideoOffset = (int) cvGetCaptureProperty(capture1, CV_CAP_PROP_FRAME_COUNT);
						 openCVstatus->AppendText("Frame offset: " +secondVideoOffset.ToString()+ "\r\n");
					 }


				}else{
					secondVideo = false;
					secondVideoOffset = 0;
				}
				*/


				 try{//open videofiles


					 if(capture1){ 
						pin_ptr<CvCapture*> p;
						p = &capture1;
						cvReleaseCapture( p ); 
					 }//release old one before create new


					 //System::String^ videofile1 = this->openFileDialog1->FileName->Replace("_data.csv","_1.mpeg");
					 const char* filename1 = (char*)(void*)Marshal::StringToHGlobalAnsi(videofileName);
					 if (!(capture1 = cvCreateFileCapture(filename1))){
						 openCVstatus->AppendText("Error opening: " +videofileName+ "\r\n");
					 }else{
						 //cvSetCaptureProperty(capture1, CV_CAP_PROP_FOURCC, CV_FOURCC('P','I','M','1') );
						int no_of_frames = (int) cvGetCaptureProperty(capture1, CV_CAP_PROP_FRAME_COUNT);
						openCVstatus->AppendText("Frames: " +no_of_frames.ToString());
						

						int intFoo;
						dataGridView1->Columns->Add("frame", "frame");
						dataGridView1->Columns["frame"]->ValueType = intFoo.GetType();
						dataGridView1->Columns["frame"]->ReadOnly = true;

						dataGridView1->Columns->Add("templateX", "templateX");//template was found at tempX tempY
						dataGridView1->Columns["templateX"]->ValueType = intFoo.GetType();
						dataGridView1->Columns->Add("templateY", "templateY");
						dataGridView1->Columns["templateY"]->ValueType = intFoo.GetType();
						dataGridView1->Columns->Add("templateFit", "templateFit");//template disimilarity; lower value is better
						dataGridView1->Columns["templateFit"]->ValueType = intFoo.GetType();
						dataGridView1->Columns->Add("belowThres", "belowThres");
						//dataGridView1->Columns["belowThres"]->ValueType = intFoo.GetType();
						 for(int i=0;i < no_of_frames; i++){
							dataGridView1->Rows->Add();
							dataGridView1->Rows[i]->Cells["frame"]->Value = i;
						}
						 show(0);//firstframe
					 }


				 }
				 catch(...){
				 }

			   loading = false;
			   msgCallback(MSG_FORM_ON, 0);//enable some user interaction with form
			 
			 }

	private: System::Void openB_Click(System::Object^  sender, System::EventArgs^  e) {


			//this->openFileDialog1->InitialDirectory = "."; 

             this->openFileDialog1->Filter = "Field-Video (*.avi)|*.avi"; 
             this->openFileDialog1->Multiselect = false; 
             this->openFileDialog1->FileName = ""; 


             if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
				 open(openFileDialog1->FileName);
             } 

	}
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

		 		 msgCallback = gcnew d_msgCallback(this, &show::Form1::updateUI); //init

				 markerComboBox->Items->Add("0272");
				 markerComboBox->Items->Add("0137");
				 markerComboBox->Items->Add("0F31");
				 markerComboBox->Items->Add("0766");
				 markerComboBox->Items->Add("12CC");
				 markerComboBox->Items->Add("18A2");
				 markerComboBox->Items->Add("2F6C");
				 markerComboBox->Items->Add("2BC1");
				 markerComboBox->Items->Add("0E3E");
				 markerComboBox->Items->Add("1F5D");
				 markerComboBox->Items->Add("47D7");
				 markerComboBox->Items->Add("1269");
				 markerComboBox->Items->Add("_TEST_");
				 markerComboBox->Text = "SELECT_MARKER";

			 }
	private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (MessageBox::Show("Are you sure you want to quit? (Did you saved your results?)", "Exit", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult ::Yes){
			e->Cancel = false;
		}else{
			e->Cancel = true;
		}
	}


public: static void myMouseHandler(int mevent, int x, int y, int flags, void* param)
{

	if (matching) return; //if matching is in progress dont allow to change the template during process

    /* user press left button */
    if (mevent == CV_EVENT_LBUTTONDOWN && !drag)
    {
		ddx = x;
		ddy = y;
        drag = 1;
    }
    /* user drag the mouse */
    if (mevent == CV_EVENT_MOUSEMOVE && drag)
    {
		if (!frame1) return; 
        mouseImg = cvCloneImage(frame1);
        cvRectangle(mouseImg,cvPoint(ddx, ddy),cvPoint(x, y),CV_RGB(255, 0, 0),1,8,0);
        cvShowImage("frameWin", mouseImg);
    }
    /* user release left button */
	
    if (mevent == CV_EVENT_LBUTTONUP && drag)
    {
		if (!frame1) return;
		//release point can be: right below | left below | left above | right above | same

		int roiX,roiY,roiW,roiH;

		if ((x-ddx > 0) && (y-ddy > 0)){//right below
			roiX = ddx; //here dragdrop started
			roiY = ddy; //here dragdrop started
			roiW = x-ddx;
			roiH = y-ddy;
		}

		if ((x-ddx <= 0) && (y-ddy <= 0)){//left above
			roiX = x;
			roiY = y;
			roiW = ddx-x; 
			roiH = ddy-y;
		}

		if ((x-ddx > 0) && (y-ddy <= 0)){//right above
			roiX = ddx;
			roiY = y;
			roiW = x-ddx; 
			roiH = ddy-y;
		}

		if ((x-ddx <= 0) && (y-ddy > 0)){//left below
			roiX = x;
			roiY = ddy;
			roiW = ddx-x; 
			roiH = y-ddy;
		}

		if ((x-ddx == 0) || (y-ddy == 0)){//same; nothing selected relase=onpress
			roiX = ddx; //here dragdrop started
			roiY = ddy; //here dragdrop started
			roiW = ddx+70;
			roiH = ddy+70;
		}

		//load current frame from video; without green rectangle for position and pupille point

		IplImage *temp;
		double frameRate = (double) cvGetCaptureProperty(capture1, CV_CAP_PROP_FPS);
		double frameTime = ((double)1000.0 * (double)currentFrame) / frameRate;
		cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_MSEC, frameTime);
		temp = cvQueryFrame(capture1);

		int actualFrame = cvGetCaptureProperty(capture1, CV_CAP_PROP_POS_FRAMES)+1;

		if (actualFrame != currentFrame){//we have a problem
			double frameRate = (double) cvGetCaptureProperty(capture1, CV_CAP_PROP_FPS);
			double frameTime = 1000.0 * (double)currentFrame / (double)frameRate - 15000;//set to 15 sec before
			cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_MSEC, frameTime);
			temp = cvQueryFrame(capture1);
			actualFrame = cvGetCaptureProperty(capture1, CV_CAP_PROP_POS_FRAMES)+1;

			if(actualFrame < currentFrame){

				//seek from -15seconds before
				for(int i=actualFrame; i < currentFrame; i++){//read until frame
					temp = cvQueryFrame(capture1);
				}

			}else{//still a problem
				//do a bruteforce sync
				cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_MSEC, 0);
				for(int i=0; i <= currentFrame; i++){
					temp = cvQueryFrame(capture1);
				}
			}
			/*
			actualFrame = cvGetCaptureProperty(capture1, CV_CAP_PROP_POS_FRAMES)+1;
			String^ soll = currentFrame.ToString();
			String^ ist = actualFrame.ToString();
			MessageBox::Show("soll:"+soll+"| ist:" +ist);
			*/
		}




		cvSetImageROI(temp, cvRect(roiX, roiY, roiW, roiH));


		templateImg1 = cvCreateImage(cvGetSize(temp),
							frame1->depth,
							frame1->nChannels);

		cvCopy(temp, templateImg1, NULL);
		if (templateImg1) cvShowImage("template", templateImg1);



		cvResetImageROI(temp);
        //cvShowImage("frameWin", frame1);
		msgCallback(MSG_SHOW_CURRENT_FRAME, 0);
        drag = 0;

    }
	

    /* user click right button: reset all */
    if (mevent == CV_EVENT_RBUTTONUP)
    {
        drag = 0;
    }
}



private: System::Void dataGridView1_RowStateChanged(System::Object^  sender, System::Windows::Forms::DataGridViewRowStateChangedEventArgs^  e) {
		 }
private: System::Void dataGridView1_Enter(System::Object^  sender, System::EventArgs^  e) {



		 }

private: System::Void  show(int row){
			 try{
			 		String^ temp = dataGridView1->Rows[row]->Cells["frame"]->Value->ToString();

					int frame = Int32::Parse(temp);
					frameLabel->Text = "frame: "+frame.ToString();

					 if (capture1){

						 //dont use this => sync problem => key frames
						//cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_FRAMES, frame);
						//frame1 = cvQueryFrame(capture1);


						double frameRate = (double) cvGetCaptureProperty(capture1, CV_CAP_PROP_FPS);
						double frameTime = ((double)1000.0 * (double)frame) / frameRate;
					    cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_MSEC, frameTime);
						frame1 = cvQueryFrame(capture1);
						currentFrame = frame;

						int actualFrame = cvGetCaptureProperty(capture1, CV_CAP_PROP_POS_FRAMES)+1;

						if (actualFrame != frame){//we have a problem
							double frameRate = (double) cvGetCaptureProperty(capture1, CV_CAP_PROP_FPS);
							double frameTime = 1000.0 * (double)frame / (double)frameRate - 15000;//set to 15 sec before
							cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_MSEC, frameTime);
							frame1 = cvQueryFrame(capture1);
							actualFrame = cvGetCaptureProperty(capture1, CV_CAP_PROP_POS_FRAMES)+1;

							if(actualFrame < frame){

								//seek from -15seconds before
								for(int i=actualFrame; i < frame; i++){//read until frame
									frame1 = cvQueryFrame(capture1);
								}

							}else{//still a problem
							   //do a bruteforce sync
								cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_MSEC, 0);
								for(int i=0; i <= frame; i++){
									frame1 = cvQueryFrame(capture1);
								}
							}
							/*
							actualFrame = cvGetCaptureProperty(capture1, CV_CAP_PROP_POS_FRAMES)+1;
							String^ soll = frame.ToString();
							String^ ist = actualFrame.ToString();
							MessageBox::Show("soll:"+soll+"| ist:" +ist);
							*/
						}




						int x,y;
						String^ tempStr;
						try{tempStr = dataGridView1->Rows[row]->Cells["templateX"]->Value->ToString();
							x = Int32::Parse(tempStr);}catch(...){x = 0;}
							//x = x/2;
						try{tempStr = dataGridView1->Rows[row]->Cells["templateY"]->Value->ToString();
							y = Int32::Parse(tempStr);}catch(...){y = 0;}
							//y = 288 - y/2;

						System::String^ belowThres = "N";
						try{tempStr = dataGridView1->Rows[row]->Cells["belowThres"]->Value->ToString();
							//belowThres = Int32::Parse(tempStr);
						     belowThres = tempStr;
						}catch(...){ belowThres = "N";}


						if (belowThres->Contains("Y")) cvRectangle(frame1,cvPoint(x, y),cvPoint(x+10, y+10),CV_RGB(0, 255, 0),2,8,0);
						

						if (frame1) cvShowImage("frameWin", frame1); // display the frame
					 }
			 }catch(...){}
		}

private: System::Void dataGridView1_CellEnter(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {


			 if (matching) return; //if matching is in progress return


			 if ((dataGridView1->SelectedRows->Count >0) && (!loading)){
				//int row = dataGridView1->CurrentCell->RowIndex;
				int row = dataGridView1->SelectedRows[0]->Index;
					String^ temp = dataGridView1->Rows[row]->Cells["frame"]->Value->ToString();

					int f = Int32::Parse(temp);
					frameLabel->Text = "frame: "+f.ToString();
					
					 if (capture1){

						show(row);// display the frame
					 }

					 
			}

		 }
private: System::Void nextB_Click(System::Object^  sender, System::EventArgs^  e) {

	try{

		int temp = dataGridView1->CurrentCell->RowIndex;
		temp++;

		if (temp < dataGridView1->Rows->Count){
			dataGridView1->FirstDisplayedScrollingRowIndex = temp;
			dataGridView1->Rows[temp]->Selected = true;
			dataGridView1->CurrentCell = dataGridView1->Rows[temp]->Cells[0];
			frameLabel->Text = "frame: "+temp.ToString();
			
		}	


			if (capture1){
				int row = dataGridView1->CurrentCell->RowIndex;

				show(row);// display the frame
				/*
				double frameRate = (double) cvGetCaptureProperty(capture1, CV_CAP_PROP_FPS);
				double frameTime = ((double)1000.0 * (double)temp) / frameRate;
				cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_MSEC, frameTime);
				frame1 = cvQueryFrame(capture1);

				if (frame1) cvShowImage("frameWin", frame1); // display the frame
				*/
			}
	}catch(...){}

	}

private: System::Void syncB_Click(System::Object^  sender, System::EventArgs^  e) {

		 }



public: Thread ^ mThread; 
public: delegate System::Int32 d_msgCallback(System::Int32, System::Int32); 
public: static d_msgCallback^ msgCallback;

public: System::Int32 updateUI(System::Int32 msg, System::Int32 i){

		   if (this->InvokeRequired) 
		   { 
			   //d_msgCallback^ invoker = gcnew d_msgCallback(this, &Form1::HSmsgCallback);
			   //array<Object^>^ args = { msg };
			   //this->Invoke(invoker, args); 
			   try{
				   this->Invoke(msgCallback,msg,i);

			   }catch(...){return -1;}
		   }else{
			   
			   if (msg == MSG_SELECT_ROW){ dataGridView1->FirstDisplayedScrollingRowIndex = i;}

			   if (msg == MSG_PROGRESS){frameLabel->Text = "processing frame: "+i.ToString() + "/"+dataGridView1->Rows->Count.ToString();}
			   if (msg == MSG_FORM_OFF){ 
				   panel1->Enabled = false; 
				   for (int i = 0; i < dataGridView1->Columns->Count; i++){
					dataGridView1->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
				 }
			   }
			   if (msg == MSG_FORM_ON){
				   panel1->Enabled = true; 
				   for (int i = 0; i < dataGridView1->Columns->Count; i++){
					dataGridView1->Columns[i]->SortMode = DataGridViewColumnSortMode::Automatic;
				 }
			   }
			   if (msg == MSG_DONE){done();}
			   if (msg == MSG_SHOW_CURRENT_FRAME){show(currentFrame);}
		   }
		   return 0;
		}

public: System::Void done(){

	frameLabel->Text = "done";


	if (batch){ 
		save(filePaths[filePathsIndex]);
		filePathsIndex++;
		batchProcess(filePathsIndex);
	}else{
		msgCallback(MSG_FORM_ON, 0);//disable some user interaction with form
	}

}

public: System::Void matchThread(){

	static IplImage* templateImg1Gray;
	static IplImage* frame1Gray;

	msgCallback(MSG_FORM_OFF, 0);//disable some user interaction with form

	matching = true; //matching is in progess; flag e.g. for mouse handler



	if (templateImg1){
		//create resultDataArray (image) used by templateMatching:
	  int resultImg_cols =  frame1->width - templateImg1->width + 1;
	  int resultImg_rows = frame1->height - templateImg1->height + 1;
	  resultImg = cvCreateImage(cvSize(resultImg_cols, resultImg_rows), IPL_DEPTH_32F, 1);


	  //create gray images:
	  templateImg1Gray = cvCreateImage(cvSize(templateImg1->width, templateImg1->height), IPL_DEPTH_8U, 1);
	  frame1Gray = cvCreateImage(cvSize(frame1->width, frame1->height), IPL_DEPTH_8U, 1);
	  cvCvtColor(templateImg1, templateImg1Gray, CV_RGB2GRAY);

	} 




  /// Localizing the best match with minMaxLoc
  double minVal; 
  double maxVal; 
  CvPoint minLoc; 
  CvPoint maxLoc;
  CvPoint matchLoc;

			int no_of_frames = (int) cvGetCaptureProperty(capture1, CV_CAP_PROP_FRAME_COUNT);
			//cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_FRAMES, 0);
			cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_MSEC, 0);//set 0


			if (dataGridView1->Rows->Count >0){
				int i;
				//for(i=0;i<dataGridView1->Rows->Count; i++){
				for(i=0;i<dataGridView1->Rows->Count; i++){
					
					int selectedPos = 5; 
					if ((i > selectedPos) && (i <(dataGridView1->Rows->Count - selectedPos))){ msgCallback(MSG_SELECT_ROW, i-selectedPos);}
					
					msgCallback(MSG_PROGRESS, i);

					if (capture1){				
						
						
						//the following gets sometimes out of sync => read every frame sequentialy and disable user interaction
						//double frameRate = (double) cvGetCaptureProperty(capture1, CV_CAP_PROP_FPS);
						//double frameTime = ((double)1000.0 * (double)i) / frameRate;
					    //cvSetCaptureProperty(capture1, CV_CAP_PROP_POS_MSEC, frameTime);
						

						frame1 = cvQueryFrame(capture1);
						//if (frame1) cvShowImage("frameWin", frame1); // display the frame

						/* template matching */
						if (templateImg1){
							//convert to gray
							cvCvtColor(frame1, frame1Gray, CV_RGB2GRAY);

							cvMatchTemplate(frame1Gray, templateImg1Gray, resultImg, CV_TM_SQDIFF_NORMED);
							cvMinMaxLoc(resultImg, &minVal, &maxVal, &minLoc, &maxLoc, 0);
							int minTemp = Math::Round(minVal*1000);
							dataGridView1->Rows[i]->Cells["templateX"]->Value = minLoc.x;
							dataGridView1->Rows[i]->Cells["templateY"]->Value = minLoc.y;
							dataGridView1->Rows[i]->Cells["templateFit"]->Value = minTemp;
							checkRowForThreshold(i);
						}

					}//if capture


				}//for
			}//if count >0


	    matching = false; //matching is NOT in progess; flag e.g. for mouse handler

		if(templateImg1Gray){//free mem
			pin_ptr<IplImage*> p;
			p = &templateImg1Gray;
			cvReleaseImage(p);
		}
		if(frame1Gray){//free mem
			pin_ptr<IplImage*> p;
			p = &frame1Gray;
			cvReleaseImage(p);
		}

		msgCallback(MSG_DONE, 0);//callback done()

	   }

private: System::Void match_Click(System::Object^  sender, System::EventArgs^  e) {


		   mThread = gcnew Thread(gcnew ThreadStart(this,&show::Form1::matchThread));
		   mThread->Start();


		 }

private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

	}

private: System::Void checkRowForThreshold(int row){


	int data = 10000;

	try{
		String^ temp = dataGridView1->Rows[row]->Cells["templateFit"]->Value->ToString();
		data = Int32::Parse(temp);
	}catch(...){
		openCVstatus->AppendText("Error while converting in row:" + row.ToString() +"\r\n" );
		//MessageBox::Show( "ERROR while converting..");

	}



	if (data < numericUpDown1->Value){//lower threshold?
		dataGridView1->Rows[row]->DefaultCellStyle->BackColor = Color::Green;
		dataGridView1->Rows[row]->Cells["belowThres"]->Value = "Y";
	}else{
		dataGridView1->Rows[row]->DefaultCellStyle->BackColor = Color::Gray;
		dataGridView1->Rows[row]->Cells["belowThres"]->Value = "N";
	}

}


private: System::Void process(){


			if (dataGridView1->Rows->Count >0){

				for(int i=0;i<dataGridView1->Rows->Count; i++){
					checkRowForThreshold(i);
				}

			}//if count >0


		 }
private: System::Void checkButton_Click(System::Object^  sender, System::EventArgs^  e) {


		 }

private: System::String^ save(System::String^ fn){

	//try{
			dataGridView1->Sort(dataGridView1->Columns["frame"], ListSortDirection::Ascending);

			DateTime^ cpCurrentDateTime = DateTime::Now;
			String^ dateStr = cpCurrentDateTime->ToString(".yyyy_MM_dd__HH_mm_ss");
			//String^ dataFilename = fn + dateStr;

			fn = fn->Replace(".avi",".d-lab");
			String^ mTemp = "marker" + markerComboBox->Text+"-";
			fn = fn->Replace("field-",mTemp);


			if (File::Exists(fn)){
				//MessageBox::Show( "ERROR: File already exists.");
				//return;

				fn = fn + dateStr;
				openCVstatus->AppendText("\r\nWARNING: File already exists. save to " +fn+"\r\n" );
			}

			IO::StreamWriter^ swFileStreamData;

			String^ newLine ="\r\n";
			String^ sep ="\t";


				swFileStreamData = gcnew IO::StreamWriter( fn, true );

				//header
				swFileStreamData->Write("frame"+sep+"x1"+sep+"y1"+sep+"x2"+sep+"y2"+sep+"x3"+sep+"y3"+sep+"x4"+sep+"y4");
				swFileStreamData->Write(newLine);

				//data
				for(int i=0;i<dataGridView1->Rows->Count; i++){

					int x; 
					int y;

					try{
						String^ tempx = dataGridView1->Rows[i]->Cells["templateX"]->Value->ToString();
						x = Int32::Parse(tempx);
						String^ tempy = dataGridView1->Rows[i]->Cells["templatey"]->Value->ToString();
						y = Int32::Parse(tempy);
					}catch(...){
						openCVstatus->AppendText("Error while converting in row:" + i.ToString() +"\r\n" );
						//MessageBox::Show( "ERROR while converting..");

					}

					String^ belowThres = dataGridView1->Rows[i]->Cells["belowThres"]->Value->ToString();

					if (belowThres->Contains("Y")){

						String^ format = "{0:####0.00}";
						//swFileStreamData->Write(secondVideoOffset + i.ToString());//offset + row/frame
						swFileStreamData->Write(i.ToString());//row/frame
						swFileStreamData->Write(sep);
						//some magic numbers 0.0x
						swFileStreamData->Write(String::Format(System::Globalization::CultureInfo::InvariantCulture,format, x + 0.01));//x1
						swFileStreamData->Write(sep);
						swFileStreamData->Write(String::Format(System::Globalization::CultureInfo::InvariantCulture,format, y + 20 + 0.01));//y1 +
						swFileStreamData->Write(sep);
						swFileStreamData->Write(String::Format(System::Globalization::CultureInfo::InvariantCulture,format, x + 0.02));//x2
						swFileStreamData->Write(sep);
						swFileStreamData->Write(String::Format(System::Globalization::CultureInfo::InvariantCulture,format, y+ 0.02));//y2
						swFileStreamData->Write(sep);
						swFileStreamData->Write(String::Format(System::Globalization::CultureInfo::InvariantCulture,format, x+ 20 +0.03));//x3 +
						swFileStreamData->Write(sep);
						swFileStreamData->Write(String::Format(System::Globalization::CultureInfo::InvariantCulture,format, y+ 0.03));//y3
						swFileStreamData->Write(sep);
						swFileStreamData->Write(String::Format(System::Globalization::CultureInfo::InvariantCulture,format, x+ 20 +0.04));//x4 +
						swFileStreamData->Write(sep);
						swFileStreamData->Write(String::Format(System::Globalization::CultureInfo::InvariantCulture,format, y+ 20 +0.04));//y4 +
						swFileStreamData->Write(sep);
						swFileStreamData->Write(newLine);
					}//"Y"
				}

				swFileStreamData->Flush();
				swFileStreamData->Close();



	//}catch(...){
		//MessageBox::Show( "ERROR while saving.");
	//	openCVstatus->AppendText("Error while saving. \r\n");
	//	return "Error while saving.";
	//}
	return "Saved to: "+fn;

}

private: System::Void saveButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->openFileDialog1->FileName){
			 String^ r = save(this->openFileDialog1->FileName);
			 MessageBox::Show(r);

		}else{
			MessageBox::Show( "ERROR while saving: No file opened.");
		}
	}

private: System::Void folderButton_Click(System::Object^  sender, System::EventArgs^  e) {



			if(folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
			  String^ folderStr = folderBrowserDialog1->SelectedPath + System::IO::Path::DirectorySeparatorChar;
			  folderLabel->Text = folderStr;
			  filePaths = Directory::GetFiles(folderStr, "field*.avi", SearchOption::AllDirectories);
			  batchButton->Text ="batch processing "+ filePaths->Length +" files";
			}

}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }


private: System::Void batchProcess(int filenummer){

	if(filePaths){

		if (filenummer >= filePaths->Length){//finish recursive calling
			msgCallback(MSG_FORM_ON, 0);//enable some user interaction with form
			batch = false;
			return;
		}



		msgCallback(MSG_FORM_OFF, 0);//disable some user interaction with form

		batchProgressLabel->Text = "batch processing "+ (filePathsIndex+1).ToString() +"/"+filePaths->Length;
		open(filePaths[filePathsIndex]);
		mThread = gcnew Thread(gcnew ThreadStart(this,&show::Form1::matchThread));
		mThread->Start();
	}else{
		batch = false;
	}

}

private: System::Void batchButton_Click(System::Object^  sender, System::EventArgs^  e) {


		if(filePaths){
			batch = true;
			filePathsIndex = 0;
			batchProcess(filePathsIndex);//process first file '0'
		}
		}
private: System::Void aboutButton_Click(System::Object^  sender, System::EventArgs^  e) {
			MessageBox::Show("This is NOT an official Dikablis(tm)/Ergoneers(tm) tool! Use at your own risk.\r\n------------------------\r\n"+
			"3-clause BSD License\r\nCopyright (c) 2014-2016 Michael Krause (krause@tum.de) Institute of Ergonomics, Technische Universität München."+
			"All rights reserved.\r\n"+
			"Redistribution and use in source and binary forms, with or without\r\n"+
			"modification, are permitted provided that the following conditions are met:\r\n"+
			"    * Redistributions of source code must retain the above copyright\r\n"+
			"      notice, this list of conditions and the following disclaimer.\r\n"+
			"    * Redistributions in binary form must reproduce the above copyright\r\n"+
			"      notice, this list of conditions and the following disclaimer in the\r\n"+
			"      documentation and/or other materials provided with the distribution.\r\n"+
			"    * Neither the name of the <organization> nor the\r\n"+
			"      names of its contributors may be used to endorse or promote products\r\n"+
			"      derived from this software without specific prior written permission.\r\n\r\n"+

			"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND"+
			"ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED"+
			"WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE"+
			"DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY"+
			"DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES"+
			"(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;"+
			"LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND"+
			"ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT"+
			"(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS"+
			"SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."+
			"\r\n-------------------\r\nThis software thanks and uses openCv (BSD licence) and Qt (e.g., LGPL) via calls. If this is the compiled executable there is a readme.txt with the licence texts.");
		 }
private: System::Void showPositionCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 show(currentFrame);
		 }
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 process();
		 }
};
}

