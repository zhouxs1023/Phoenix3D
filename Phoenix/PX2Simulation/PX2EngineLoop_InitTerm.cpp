// PX2EngineLoop_InitTerm.cpp

#include "PX2EngineLoop.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
bool EngineLoop::PreInitlize()
{
#ifdef PX2_USE_MEMORY
	Memory::Initialize();
#endif

	return true;
}
//----------------------------------------------------------------------------
bool EngineLoop::Initlize()
{
	time_t ti; time(&ti); srand((unsigned int)ti);

	StringHelp::Initlize();
	FString::Initlize();

	Logger *logger = new0 Logger();

#if defined(_WIN32) || defined(WIN32)
	logger->AddFileHandler("PX2Application_Log.txt", LT_INFO | LT_ERROR | LT_USER);
#endif
	logger->AddOutputWindowHandler(LT_INFO | LT_ERROR | LT_USER);
	logger->StartLogger();

	DateTime time;
	int year1 = time.Year();
	int month1 = time.Month();
	int week1 = time.Week();
	int day1 = time.Day();
	int dayOfWeek1 = time.DayOfWeek();
	int dayOfYear1 = time.DayOfYear();
	int hour1 = time.Hour();
	int minute1 = time.Minute();
	int second1 = time.Second();
	int millisecond1 = time.Millisecond();
	int microsecond1 = time.Microsecond();
	PX2_LOG_INFO("Year:%d; Month:%d; Week:%d; Day:%d; DayOfWeek:%d; DayOfYear:%d; Hour:%d; Minute:%d; Second:%d; Millisecond:%d; Microsecond:%d",
		year1, month1, week1, day1, dayOfWeek1, dayOfYear1, hour1, minute1, second1, millisecond1, microsecond1);

	mTimerMan = new0 TimerManager();

	mIMEDisp = new0 IMEDispatcher();

	mLanguageMan = new0 LanguageManager();
	mResMan = new0 ResourceManager();

	//PX2_LM.Add("Data/engine/engineLanguage.csv");

	mEventWorld = new0 EventWorld();

	//mScriptMan = new0 LuaManager();
	//mScriptMan->Create();
	//LuaManager *luaMan = (LuaManager*)mScriptMan;
	//tolua_PX2_open(luaMan->GetLuaState());

	mRoot = new0 GraphicsRoot();
	mRoot->Initlize();

	mFontMan = new0 FontManager();
	PX2_UNUSED(mFontMan);

	mADMan = new0 AddDeleteManager();
	PX2_UNUSED(mADMan);

	mUIManager = new0 UIManager();
	mUIManager->ComeInEventWorld();

	mAccoutManager = new0 AccoutManager();

	return true;
}
//----------------------------------------------------------------------------
void EngineLoop::WillEnterForeground(bool isFirstTime)
{
	if (!mIsInBackground)
		return;

	if (isFirstTime)
	{
		PX2_FM.Initlize();
	}
	else
	{
#ifdef PX2_USE_OPENGLES2
		Renderer::GetDefaultRenderer()->OnRestoreDevice();
#endif

		PX2_FM.SetNeedUpdate();
	}

	//	PX2_SS.EnableMusic(mBeforeInBackgroundMusicEnable);
	//	PX2_SS.EnableSounds(mBeforeInBackgroundSoundEnable);

	//PX2_SOUNDM.PreLoad();

	mIsInBackground = false;
}
//----------------------------------------------------------------------------
void EngineLoop::DidEnterBackground()
{
	PX2_FM.Terminate();
	PX2_AM.DeleteAllUsers();
	PX2_UIM.Clear();
	PX2_ADM.Clear();;
	PX2_RM.Clear();
	PX2_SM.Clear();
	PX2_TimerM.ClearTimers();

	//mBeforeInBackgroundMusicEnable = PX2_SS.IsMusicEnable();
	//mBeforeInBackgroundSoundEnable = PX2_SS.IsSoundEnable();
	//PX2_SS.EnableMusic(false);
	//PX2_SS.EnableSounds(false);

#ifdef PX2_USE_OPENGLES2
	Renderer::GetDefaultRenderer()->OnLostDevice();
#endif

	mIsInBackground = true;
}
//----------------------------------------------------------------------------
bool EngineLoop::Ternamate()
{
	if (mADMan)
	{
		mADMan->Clear();
		delete0(mADMan);
		AddDeleteManager::Set(0);
	}

	if (mAccoutManager)
	{
		delete0(mAccoutManager);
		AccoutManager::Set(0);
	}

	if (mResMan)
	{
		mResMan->Clear();
	}

	if (mUIManager)
	{
		mUIManager->Clear();
		delete0(mUIManager);
		UIManager::Set(0);
	}

	if (mScriptMan)
	{
		delete0(mScriptMan);
		ScriptManager::Set(0);
	}

	if (mFontMan)
	{
		delete0(mFontMan);
		FontManager::Set(0);
	}

	if (mScriptMan)
	{
		delete0(mScriptMan);
		ScriptManager::Set(0);
	}

	if (mRoot)
	{
		mRoot->Terminate();
		delete0(mRoot);
		GraphicsRoot::Set(0);
	}

	if (mResMan)
	{
		delete0(mResMan);
		ResourceManager::Set(0);
	}

	if (mLanguageMan)
	{
		delete0(mLanguageMan);
		LanguageManager::Set(0);
	}

	if (mIMEDisp)
	{ // 需要在资源管理器之后释放
		delete0(mIMEDisp);
		IMEDispatcher::Set(0);
	}

	if (mEventWorld)
	{
		delete0(mEventWorld);
		EventWorld::Set(0);
	}

	if (mTimerMan)
	{
		delete0(mTimerMan);
		TimerManager::Set(0);
	}

	Renderer *defaultRenderer = Renderer::GetDefaultRenderer();
	if (defaultRenderer)
	{
		delete0(defaultRenderer);
		Renderer::SetDefaultRenderer(0);
	}

	Logger *logger = Logger::GetSingletonPtr();
	if (logger)
	{
		delete0(logger);
		Logger::Set(0);
	}

	FString::Ternimate();

	return true;
}
//----------------------------------------------------------------------------
bool EngineLoop::AfterTernamate()
{
#ifdef PX2_USE_MEMORY
	Memory::Terminate("PX2Application_MemoryReport.txt", false);
#endif

	return true;
}
//----------------------------------------------------------------------------