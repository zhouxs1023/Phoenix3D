// PX2_NirMan.cpp

#include "PX2E_NirMan.hpp"
#include "PX2Edit.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2E_MainFrame.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(NirMan, wxEvtHandler)
END_EVENT_TABLE();
//----------------------------------------------------------------------------
NirMan::NirMan():
mCurMenu(0)
{
}
//----------------------------------------------------------------------------
NirMan::~NirMan()
{
}
//----------------------------------------------------------------------------
bool NirMan::Initlize()
{
	return true;
}
//----------------------------------------------------------------------------
bool NirMan::Ternamate()
{
	return true;
}
//----------------------------------------------------------------------------
void NirMan::SetCurMenu(wxMenu *menu)
{
	mCurMenu = menu;
}
//----------------------------------------------------------------------------
wxMenu *NirMan::GetCurMenu()
{
	return mCurMenu;
}
//----------------------------------------------------------------------------
wxMenu *NirMan::AddSubMenu(wxMenu *menu, const std::string &title)
{
	wxMenu *subMenu = new wxMenu();
	menu->AppendSubMenu(subMenu, title);

	return subMenu;
}
//----------------------------------------------------------------------------
wxMenuItem *NirMan::AddMenuItem(wxMenu *menu, const std::string &title,
	const std::string &script)
{
	return E_MainFrame::GetSingletonPtr()->AddMenuItem(menu, title, script);
}
//----------------------------------------------------------------------------
void NirMan::AddSeparater(wxMenu *menu)
{
	menu->AppendSeparator();
}
//----------------------------------------------------------------------------