#pragma once
#include "PopWnd.h"
#include "ShlObj.h"
#include "MsgWnd.h"
#include "ControlEx.h"

class CDemoFrame : public WindowImplBase, public CWebBrowserEventHandler, public SkinChangedReceiver
{
public:
	CDemoFrame() 
	{
		m_pPopWnd = NULL;
		m_pMenu = NULL;
	}

public:
	CControlUI* CreateControl(LPCTSTR pstrClass)
	{
		if(lstrcmpi(pstrClass, _T("CircleProgress" )) == 0) {
			return new CCircleProgressUI();
		}
		return NULL;
	}
	// ��ʼ����Դ������
	void InitResource()
	{
		// �����Խӿ�
		CResourceManager::GetInstance()->SetTextQueryInterface(this);
		// ע��ؼ�
		REGIST_DUICONTROL(CCircleProgressUI);
		REGIST_DUICONTROL(CChartViewUI);
		// ������Դ
		if (GetResourceType() == UILIB_RESOURCE)
		{
			// ������Դ������
			CResourceManager::GetInstance()->LoadResource(_T("IDR_RES"), _T("xml"));
		}
		else {
			// ������Դ������
			CResourceManager::GetInstance()->LoadResource(_T("res.xml"), NULL);
		}	
	}
	void InitWindow() 
	{
		CSkinManager::GetSkinManager()->AddReceiver(this);

		m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
		m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
		m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
		m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
		m_pSkinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("skinbtn")));
		CWebBrowserUI* pBrowser1 = static_cast<CWebBrowserUI*>(m_pm.FindControl(_T("oneclick_browser1")));
		pBrowser1->SetWebBrowserEventHandler(this);
		CWebBrowserUI* pBrowser2 = static_cast<CWebBrowserUI*>(m_pm.FindControl(_T("oneclick_browser2")));
		pBrowser2->SetWebBrowserEventHandler(this);
		pBrowser1->NavigateUrl(_T("http://blog.csdn.net/duisharp"));
		pBrowser2->NavigateUrl(_T("http://www.51haoliandan.com"));

		CComboUI* pFontSize = static_cast<CComboUI*>(m_pm.FindControl(_T("font_size")));
		if(pFontSize)
		{
			CListLabelElementUI * pElement = new CListLabelElementUI();
			pElement->SetText(_T("���Գ�����"));
			pElement->SetFixedHeight(30);
			pElement->SetFixedWidth(120);
			pFontSize->Add(pElement);
		}
		CComboUI* pCombo = new CComboUI();
		pCombo->SetName(_T("mycombo"));
		pCombo->SetFixedWidth(80);
		pCombo->ApplyAttributeList(m_pm.GetStyle(_T("combo_style")));
		CContainerUI* pParent = (CContainerUI*)pFontSize->GetParent();
		pParent->Add(pCombo);
		if(pCombo)
		{
			pCombo->SetItemFont(2);
			CListLabelElementUI * pElement = new CListLabelElementUI();
			pElement->SetText(_T("��̬����"));
			pElement->SetFixedHeight(30);
			pElement->SetFixedWidth(120);
			pCombo->Add(pElement);
			pCombo->SelectItem(0);
		}
		CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("listview")));

		CListContainerElementUI* pListItem  = new CListContainerElementUI();
		pListItem->SetBorderColor(0xFF00FF00);
		pListItem->SetBorderSize(1);
		pListItem->SetBorderStyle(PS_DASHDOTDOT);
		pListItem->SetFixedHeight(30);
		pListItem->SetManager(&m_pm, NULL, false);
		pList->Add(pListItem);
		CButtonUI* pBtn1 = new CButtonUI();
		pBtn1->SetManager(&m_pm, NULL, false);
		pBtn1->SetAttribute(_T("style"), _T("btn_style"));
		pBtn1->SetText(_T("����"));
		pListItem->Add(pBtn1);
		CButtonUI* pBtn2 = new CButtonUI();
		pBtn2->SetManager(&m_pm, NULL, false);
		pBtn2->SetAttribute(_T("style"), _T("btn_style"));
		pBtn2->SetText(_T("20001"));
		pListItem->Add(pBtn2);

		CDialogBuilder builder1;
		CListContainerElementUI* pListItem1  = (CListContainerElementUI*)builder1.Create(_T("listitem.xml"), NULL, this, &m_pm, NULL);
		pList->Add(pListItem1);

		for(int i = 0; i < 20; i++)
		{
			CListTextElementUI* pItem  = new CListTextElementUI();
			pItem->SetFixedHeight(30);
			pList->Add(pItem);
			pItem->SetText(0, _T("����"));
			pItem->SetText(1, _T("1000"));
			pItem->SetText(2, _T("100"));
		}
		
		CTreeViewUI* pTreeView = static_cast<CTreeViewUI*>(m_pm.FindControl(_T("treeview")));
		CTreeNodeUI* pItem  = new CTreeNodeUI();
		pItem->SetFixedHeight(30);
		pItem->SetItemText(_T("��̬���"));
		pTreeView->Add(pItem);
		pItem->SetAttribute(_T("itemattr"), _T("valign=&quot;center&quot;"));
		pItem->SetAttribute(_T("Style"), _T("treeview_style"));

		CDialogBuilder builder;
		CTreeNodeUI* pTreeItem = (CTreeNodeUI*)builder.Create(_T("treeitem.xml"), NULL, this, &m_pm, pTreeView);
		pTreeView->Add(pTreeItem);

		// ͼ��ؼ�
		CChartViewUI *pHistpgramView = static_cast<CChartViewUI*>(m_pm.FindControl(_T("ChartView_Histpgram")));
		if (NULL != pHistpgramView)
		{
			pHistpgramView->Add(_T("1��{c #FE5900}13%{/c}"), 13);
			pHistpgramView->Add(_T("2��{c #FE5900}11%{/c}"), 11);
			pHistpgramView->Add(_T("3��{c #FE5900}32%{/c}"), 32);
			pHistpgramView->Add(_T("4��{c #FE5900}17%{/c}"), 17);
			pHistpgramView->Add(_T("5��{c #FE5900}8%{/c}"), 8);
			pHistpgramView->Add(_T("6��{c #FE5900}12%{/c}"), 12);
		}

		CChartViewUI *pPieView = static_cast<CChartViewUI*>(m_pm.FindControl(_T("ChartView_Pie")));
		if (NULL != pPieView)
		{
			pPieView->Add(_T("����{c #FE5900}35%{/c}"), 35);
			pPieView->Add(_T("�Ϻ�{c #FE5900}38%{/c}"), 38);
			pPieView->Add(_T("����{c #FE5900}35%{/c}"), 35);
			pPieView->Add(_T("���{c #FE5900}15%{/c}"), 15);
		}
	}

	virtual BOOL Receive(SkinChangedParam param)
	{
		CControlUI* pRoot = m_pm.FindControl(_T("root"));
		if( pRoot != NULL ) {
			if( param.bColor ) {
				pRoot->SetBkColor(param.bkcolor);
				pRoot->SetBkImage(_T(""));
			}
			else {
				pRoot->SetBkColor(0);
				pRoot->SetBkImage(param.bgimage);
				m_pm.SetLayeredImage(param.bgimage);
			}
		}
		return TRUE;
	}

	virtual HRESULT STDMETHODCALLTYPE UpdateUI( void)
	{
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE GetHostInfo(CWebBrowserUI* pWeb, 
		/* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo)
	{
		if (pInfo != NULL) {
			pInfo->dwFlags |= DOCHOSTUIFLAG_NO3DBORDER | DOCHOSTUIFLAG_NO3DOUTERBORDER;
		}
		return S_OK;
	}
public:

	DuiLib::CDuiString GetSkinFolder()
	{
#ifdef _DEBUG
		return _T("skin\\duidemo\\");
#else
		return _T("skin\\");
#endif
	}

	DuiLib::CDuiString GetSkinFile()
	{
		return _T("XML_MAIN");
	}

	UILIB_RESOURCETYPE GetResourceType() const
	{
#ifdef _DEBUG
		return UILIB_FILE;
#else
		return UILIB_ZIPRESOURCE;
#endif
	}

	LPCTSTR GetResourceID() const
	{
		return _T("IDR_ZIPRES");
	}

	DuiLib::CDuiString GetZIPFileName() const
	{
		return _T("skin.zip");
	}


	LPCTSTR GetWindowClassName() const
	{ 
		return _T("MainWnd");
	}

	UINT GetClassStyle() const
	{ 
		return CS_DBLCLKS; 
	}

	void OnFinalMessage(HWND hWnd)
	{ 
		delete this;
	}

	LPCTSTR QueryControlText(LPCTSTR lpstrId, LPCTSTR lpstrType)
	{
		CDuiString sLanguage = CResourceManager::GetInstance()->GetLanguage();
		if(sLanguage == _T("en")){
			if(lstrcmpi(lpstrId, _T("lantext")) == 0) {
				return _T("Switch to Chinese");
			}
			else if(lstrcmpi(lpstrId, _T("titletext")) == 0) {
				return _T("Duilib Demo v1.1");
			}
			else if(lstrcmpi(lpstrId, _T("hometext")) == 0) {
				return _T("{a}Home Page{/a}");
			}
		}
		else{
			if(lstrcmpi(lpstrId, _T("lantext")) == 0) {
				return _T("�л���Ӣ��");
			}
			else if(lstrcmpi(lpstrId, _T("titletext")) == 0) {
				return _T("Duilib ʹ����ʾ v1.1");
			}
			else if(lstrcmpi(lpstrId, _T("hometext")) == 0) {
				return _T("{a}��ʾ����{/a}");
			}
		}

		return NULL;
	}

	void Notify(TNotifyUI& msg)
	{
		if( msg.sType == _T("showactivex") ) 
		{
			if( msg.pSender->GetName().CompareNoCase(_T("ani_flash")) == 0 ) 
			{
				IShockwaveFlash* pFlash = NULL;
				CActiveXUI* pActiveX = static_cast<CActiveXUI*>(msg.pSender);
				pActiveX->GetControl(__uuidof(IShockwaveFlash), (void**)&pFlash);
				if( pFlash != NULL ) 
				{
					pFlash->put_WMode( _bstr_t(_T("Transparent") ) );
					pFlash->put_Movie( _bstr_t(CPaintManagerUI::GetInstancePath() + _T("\\skin\\duidemo\\waterdrop.swf")) );
					pFlash->DisableLocalSecurity();
					pFlash->put_AllowScriptAccess(L"always");
					BSTR response;
					pFlash->CallFunction(L"<invoke name=\"setButtonText\" returntype=\"xml\"><arguments><string>Click me!</string></arguments></invoke>", &response);
					pFlash->Release();
				}  
			}
		}
		else if( msg.sType == _T("click") )
		{
			if( msg.pSender == m_pCloseBtn ) 
			{
				if(IDYES == MessageBox(m_hWnd, _T("ȷ���˳�duidemo��ʾ����"), _T("Duilib�콢��"), MB_YESNO))
				{
					PostQuitMessage(0);
				}
				return; 
			}
			else if( msg.pSender == m_pMinBtn ) { 
				SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
			else if( msg.pSender == m_pMaxBtn ) { 
				SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
			else if( msg.pSender == m_pRestoreBtn ) { 
				SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
			else if( msg.pSender == m_pSkinBtn ) {
				new CSkinFrame(m_hWnd, m_pSkinBtn);
			}
			// ��ť��Ϣ
			OnLClick(msg.pSender);
		}
		else if(msg.sType==_T("selectchanged"))
		{
			CDuiString name = msg.pSender->GetName();
			CTabLayoutUI* pTabSwitch = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("tab_switch")));

			if(name.CompareNoCase(_T("basic_tab")) == 0) pTabSwitch->SelectItem(0);
			if(name.CompareNoCase(_T("rich_tab")) == 0) pTabSwitch->SelectItem(1);
			if(name.CompareNoCase(_T("ani_tab")) == 0) pTabSwitch->SelectItem(2);
			if(name.CompareNoCase(_T("split_tab")) == 0) pTabSwitch->SelectItem(3);
		}
		else if(msg.sType == _T("valuechanged"))
		{
			CProgressUI* pSlider = static_cast<CProgressUI*>(m_pm.FindControl(_T("slider")));
			CProgressUI* pPro1 = static_cast<CProgressUI*>(m_pm.FindControl(_T("progress")));
			CProgressUI* pPro2 = static_cast<CProgressUI*>(m_pm.FindControl(_T("circle_progress")));
			pPro1->SetValue(pSlider->GetValue());
			pPro2->SetValue(pSlider->GetValue());
		}
	}
	void OnLClick(CControlUI *pControl)
	{
		CDuiString sName = pControl->GetName();
		if(sName.CompareNoCase(_T("homepage_btn")) == 0)
		{
			ShellExecute(NULL, _T("open"), _T("https://github.com/qdtroy"), NULL, NULL, SW_SHOW);
		}
		else if(sName.CompareNoCase(_T("button1")) == 0)
		{
			CEditUI* pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("edit3")));
			TCHAR* pstrText = (TCHAR*)pEdit->GetText().GetData();
			if(pstrText != NULL && lstrlen(pstrText) > 0) {
				double fEdit = _ttof(pstrText);
				MessageBox(m_hWnd, pstrText, _T(""), 0);
			}
		}
		else if(sName.CompareNoCase(_T("popwnd_btn")) == 0)
		{
			if(m_pPopWnd == NULL)
			{
				m_pPopWnd = new CPopWnd();
			}
			if(!::IsWindow(*m_pPopWnd))
			{
				m_pPopWnd->Create(m_hWnd, _T("͸��������ʾ"), WS_POPUP | WS_VISIBLE, WS_EX_TOOLWINDOW, 0, 0, 800, 572);
			}
			m_pPopWnd->CenterWindow();
		}
		else if(sName.CompareNoCase(_T("modal_popwnd_btn")) == 0)
		{
			if(m_pPopWnd == NULL)
			{
				m_pPopWnd = new CPopWnd();
			}
			else if(IsWindow(*m_pPopWnd)) {
				DestroyWindow(*m_pPopWnd);
			}
			if(!::IsWindow(*m_pPopWnd))
			{
				m_pPopWnd->Create(m_hWnd, _T("͸��������ʾ"), WS_POPUP | WS_VISIBLE, WS_EX_TOOLWINDOW, 0, 0, 800, 572);
			}
			m_pPopWnd->CenterWindow();
			m_pPopWnd->ShowModal();
		}

		else if(sName.CompareNoCase(_T("qqgroup_btn")) == 0)
		{
			TCHAR szPath[MAX_PATH] ={0};
			SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES | CSIDL_FLAG_CREATE, NULL, 0, szPath);
			CDuiString sIEPath;
			sIEPath.Format(_T("%s\\Internet Explorer\\iexplore.exe"), szPath);
			ShellExecute(NULL, _T("open"), sIEPath, _T("http://jq.qq.com/?_wv=1027&k=cDTUzr"), NULL, SW_SHOW);
		}
		else if(sName.CompareNoCase(_T("qq_btn")) == 0)
		{
			TCHAR szPath[MAX_PATH] ={0};
			SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES | CSIDL_FLAG_CREATE, NULL, 0, szPath);
			CDuiString sIEPath;
			sIEPath.Format(_T("%s\\Internet Explorer\\iexplore.exe"), szPath);
			ShellExecute(NULL, _T("open"), sIEPath, _T("tencent://Message/?Uin=656067418&Menu=yes"), NULL, SW_SHOW);
		}
		else if(sName.CompareNoCase(_T("menubtn")) == 0)
		{
			if(m_pMenu != NULL) {
				delete m_pMenu;
				m_pMenu = NULL;
			}
			m_pMenu = new CMenuWnd();
			CDuiPoint point;
			::GetCursorPos(&point);
			
			m_pMenu->Init(NULL, _T("menu.xml"), point, &m_pm);
			CMenuUI* rootMenu = m_pMenu->GetMenuUI();
			if (rootMenu != NULL)
			{
				CMenuElementUI* pNew = new CMenuElementUI;
				pNew->SetName(_T("Menu_Dynamic"));
				pNew->SetText(_T("��̬һ���˵�"));
				pNew->SetShowExplandIcon(true);
				pNew->SetIcon(_T("WebSit.png"));
				pNew->SetIconSize(16,16);

				CMenuElementUI* pSubNew = new CMenuElementUI;
				pSubNew->SetText(_T("��̬�����˵�"));
				pSubNew->SetName(_T("Menu_Dynamic"));
				pSubNew->SetIcon(_T("Virus.png"));
				pSubNew->SetIconSize(16,16);
				pNew->Add(pSubNew);
				rootMenu->Add(pNew);

				CMenuElementUI* pNew2 = new CMenuElementUI;
				pNew2->SetName(_T("Menu_Dynamic"));
				pNew2->SetText(_T("��̬һ���˵�2"));
				rootMenu->AddAt(pNew2,2);
			}

			// ��̬��Ӻ��������ò˵��Ĵ�С
			m_pMenu->ResizeMenu();
		}
	}

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
		if( wParam == SC_CLOSE ) {
			::PostQuitMessage(0L);
			bHandled = TRUE;
			return 0;
		}
		BOOL bZoomed = ::IsZoomed(*this);
		LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		if( ::IsZoomed(*this) != bZoomed ) {
			if( !bZoomed ) {
				CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
				if( pControl ) pControl->SetVisible(false);
				pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
				if( pControl ) pControl->SetVisible(true);
			}
			else {
				CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
				if( pControl ) pControl->SetVisible(true);
				pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
				if( pControl ) pControl->SetVisible(false);
			}
		}
		return lRes;
	}

	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// �رմ��ڣ��˳�����
		if(uMsg == WM_DESTROY)
		{
			::PostQuitMessage(0L);
			bHandled = TRUE;
			return 0;
		}
		else if (uMsg == WM_MENUCLICK)
		{
			MenuCmd* pMenuCmd = (MenuCmd*)wParam;
			if(pMenuCmd != NULL)
			{
				BOOL bChecked = pMenuCmd->bChecked;
				CDuiString sMenuName = pMenuCmd->szName;
				CDuiString sUserData = pMenuCmd->szUserData;
				CDuiString sText = pMenuCmd->szText;
				m_pm.DeletePtr(pMenuCmd);

				if(sMenuName.CompareNoCase(_T("lan")) == 0)
				{
					static bool bEn = false;
					if(!bEn) {
						CResourceManager::GetInstance()->SetLanguage(_T("en"));
					}
					else {
						CResourceManager::GetInstance()->SetLanguage(_T("cn_zh"));					
					}
					bEn = !bEn;
					CResourceManager::GetInstance()->ReloadText();
					InvalidateRect(m_hWnd, NULL, TRUE);
					m_pm.NeedUpdate();
				}
				else if (sMenuName == _T("qianting"))
				{
					if (bChecked)
					{
						CMsgWnd::MessageBox(m_hWnd, NULL, _T("��Ԥ����Ǳͧ����"));
					} 
					else
					{
						CMsgWnd::MessageBox(m_hWnd, NULL, _T("��ȡ����Ǳͧ����"));
					}			 
				}
				else
				{
					CMsgWnd::MessageBox(m_hWnd, NULL, sText);
				}
			}
			if(m_pMenu != NULL) {
				delete m_pMenu;
				m_pMenu = NULL;
			}
			bHandled = TRUE;
			return 0;
		}
		bHandled = FALSE;
		return 0;
	}

private:
	CPopWnd* m_pPopWnd;
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;
	CButtonUI* m_pSkinBtn;
	CMenuWnd* m_pMenu;
	std::map<CDuiString, bool> m_MenuInfos;
};
