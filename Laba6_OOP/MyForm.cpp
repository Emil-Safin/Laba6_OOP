#include "MyForm.h"
#include "List.h"
#include "Handler.h"
#include "Figures.h"
#include "Circle.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Lab6OOP::MyForm form;
	Application::Run(% form); 
}