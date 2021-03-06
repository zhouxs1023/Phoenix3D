// PX2EngineLoop.hpp

#ifndef PX2ENGINELOOP_HPP
#define PX2ENGINELOOP_HPP

#include "PX2Singleton.hpp"
#include "PX2TimerManager.hpp"
#include "PX2EventWorld.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2IMEDispatcher.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2FontManager.hpp"
#include "PX2AddDeleteManager.hpp"
#include "PX2UIManager.hpp"
#include "PX2Selection.hpp"
#include "PX2RedoUndo.hpp"
#include "PX2Creater.hpp"
#include "PX2AccoutManager.hpp"

namespace PX2
{

	class RendererInput;

	class EngineLoop
	{
		PX2_SINGLETION(EngineLoop);

		// pre init
	public:
		void SetPt_Data(void *data);
		void *GetPt_Data();
		void SetPt_Size(const Sizef &size);
		const Sizef &GetPt_Size() const;

	protected:
		void *mPt_Data;
		Sizef mPt_Size;

		// init term
	public:
		bool Initlize();
		bool InitlizeRenderer();

		void WillEnterForeground(bool isFirstTime);
		void DidEnterBackground();

		bool Ternamate();

	public_internal:
		Renderer *CreateRenderer(void *ptData, int width, int height, 
			int numMultisamples, RendererInput* &renderInput);

	private:
		RendererInput *mRendererInput;

		TimerManager *mTimerMan;
		EventWorld *mEventWorld;
		LanguageManager *mLanguageMan;
		ScriptManager *mScriptMan;
		GraphicsRoot *mRoot;
		IMEDispatcher *mIMEDisp;
		ResourceManager *mResMan;
		FontManager *mFontMan;
		AddDeleteManager *mADMan;
		Selection *mSelection;
		Creater *mCreater;
		URDoManager *mURDoMan;
		UIManager *mUIManager;
		AccoutManager *mAccoutManager;

	protected:
		bool mIsInBackground;

		bool mBeforeInBackgroundMusicEnable;
		bool mBeforeInBackgroundSoundEnable;

		// boost
	public:
		bool LoadBoost(const std::string &filename);
		const Sizef &GetBoostSize() const;
		const std::string &GetProjectPath() const;

	protected:
		Sizef mBoostSize;
		std::string mProjectPath;

		// public
	public:
		void SetSize(const Sizef &size);
		const Sizef &GetSize() const;

	protected:
		Sizef mSize;

		// Tick
	public:
		void Tick();
		float GetElapsedTime();

	private:
		double mAppTime;
		double mLastAppTime;
		double mElapsedTime;

		// Play
	public:
		enum PlayType
		{
			PT_NONE,
			PT_SIMULATE,
			PT_PLAY,
			PT_MAX_TYPE
		};
		void Play(PlayType type);
		PlayType GetPlayType() const;
		
	protected:
		PlayType mPlayType;
	};

#include "PX2EngineLoop.inl"
#define PX2_ENGINELOOP EngineLoop::GetSingleton()

}

#endif