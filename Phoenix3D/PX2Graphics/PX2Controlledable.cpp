/*
*
* 文件名称	：	PX2Controlledable.cpp
*
*/

#include "PX2Controlledable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Componable, Controlledable);
PX2_IMPLEMENT_STREAM(Controlledable);
PX2_IMPLEMENT_ABSTRACT_FACTORY(Controlledable);

//----------------------------------------------------------------------------
Controlledable::Controlledable ()
	:
mIsSelfCtrled(false)
{
	mControlUpdateTimeLast = -1.0;
	mControlUpdateTimeMin = 0.02;
}
//----------------------------------------------------------------------------
Controlledable::~Controlledable ()
{
}
//----------------------------------------------------------------------------
void Controlledable::ResetPlay ()
{
	Reset();
	Play();
}
//----------------------------------------------------------------------------
void Controlledable::Play ()
{
	for (int i=0; i<GetNumControllers(); i++)
	{
		mControllers[i]->Play();
	}
}
//----------------------------------------------------------------------------
bool Controlledable::IsPlaying () const
{
	for (int i=0; i<GetNumControllers(); i++)
	{
		if (mControllers[i]->IsPlaying())
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Controlledable::Stop ()
{
	for (int i=0; i<GetNumControllers(); i++)
	{
		mControllers[i]->Stop();
	}
}
//----------------------------------------------------------------------------
void Controlledable::Reset ()
{
	for (int i=0; i<GetNumControllers(); i++)
	{
		mControllers[i]->Reset();
	}
}
//----------------------------------------------------------------------------
void Controlledable::SetSelfCtrled (bool selfCtrled)
{
	mIsSelfCtrled = selfCtrled;
}
//----------------------------------------------------------------------------
Controller *Controlledable::GetController (const std::string &name) const
{
	for (int i=0; i<GetNumControllers(); i++)
	{
		if (mControllers[i]->GetName() == name)
			return mControllers[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
bool Controlledable::HasController (Controller* controller)
{
	for (int i=0; i<GetNumControllers(); i++)
	{
		if (mControllers[i] == controller)
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Controlledable::AttachController (Controller* controller)
{
	// 控制器必须存在
	if (!controller)
	{
		assertion(false, "Cannot attach a null controller\n");
		return;
	}

	if (HasController(controller))
		return;

	mControllers.push_back(controller);
	controller->SetControlledable(this);
	controller->OnAttach();

	SortControls();
}
//----------------------------------------------------------------------------
void Controlledable::DetachController (Controller* controller)
{
	std::vector<ControllerPtr>::iterator it = mControllers.begin();

	for (; it!=mControllers.end(); it++)
	{
		if (controller == *it)
		{
			controller->OnDetach();
			controller->SetControlledable(0);
			mControllers.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------
void Controlledable::DetachAllControllers ()
{
	for (int i=0; i<GetNumControllers(); ++i)
	{
		// Unbind
		mControllers[i]->OnDetach();
		mControllers[i]->SetControlledable(0);
	}

	mControllers.clear();
}
//----------------------------------------------------------------------------
void Controlledable::SortControls ()
{
	std::sort(mControllers.begin(), mControllers.end(), Controller::LessThan);
}
//----------------------------------------------------------------------------
bool Controlledable::UpdateControllers (double applicationTime)
{
	bool someoneUpdated = false;

	for (int i = 0; i < GetNumControllers(); ++i)
	{
		if (mControllers[i]->Update(applicationTime))
		{
			someoneUpdated = true;
		}
	}

	return someoneUpdated;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void Controlledable::RegistProperties ()
{
	Componable::RegistProperties();

	AddPropertyClass("Controlledable");

	AddProperty("IsSelfCtrled", PT_BOOL, mIsSelfCtrled);
}
//----------------------------------------------------------------------------
void Controlledable::OnPropertyChanged (const PropertyObject &obj)
{
	Componable::OnPropertyChanged(obj);

	if ("IsSelfCtrled" == obj.Name)
	{
		SetSelfCtrled(PX2_ANY_AS(obj.Data, bool));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Controlledable::GetObjectByName(const std::string& name)
{
	Object* found = Componable::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	for (int i = 0; i < GetNumControllers(); ++i)
	{
		PX2_GET_OBJECT_BY_NAME(mControllers[i], name, found);
	}

	return 0;
}
//----------------------------------------------------------------------------
void Controlledable::GetAllObjectsByName (const std::string& name,
											std::vector<Object*>& objects)
{
	Componable::GetAllObjectsByName(name, objects);

	for (int i = 0; i < GetNumControllers(); ++i)
	{
		PX2_GET_ALL_OBJECTS_BY_NAME(mControllers[i], name, objects);
	}
}
//----------------------------------------------------------------------------
Object* Controlledable::GetObjectByID(int id)
{
	Object* found = Componable::GetObjectByID(id);
	if (found)
	{
		return found;
	}

	for (int i = 0; i < GetNumControllers(); ++i)
	{
		PX2_GET_OBJECT_BY_ID(mControllers[i], id, found);
	}

	return 0;
}
//----------------------------------------------------------------------------
void Controlledable::GetAllObjectsByID(int id,
	std::vector<Object*>& objects)
{
	Componable::GetAllObjectsByID(id, objects);

	for (int i = 0; i < GetNumControllers(); ++i)
	{
		PX2_GET_ALL_OBJECTS_BY_ID(mControllers[i], id, objects);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Controlledable::Controlledable (LoadConstructor value)
:
Componable(value),
mIsSelfCtrled(false),
mControllers(0)
{
	mControlUpdateTimeLast = -1.0;
	mControlUpdateTimeMin = 0.02;
}
//----------------------------------------------------------------------------
void Controlledable::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Componable::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadBool(mIsSelfCtrled);

	int numCtrls;
	source.Read(numCtrls);
	mControllers.resize(numCtrls);
	for (int i=0; i<numCtrls; i++)
	{
		source.ReadPointer(mControllers[i]);
	}

	PX2_END_DEBUG_STREAM_LOAD(Controlledable, source);
}
//----------------------------------------------------------------------------
void Controlledable::Link (InStream& source)
{
	Componable::Link(source);

	int numCtrls = (int)mControllers.size();
	for (int i=0; i<numCtrls; i++)
	{
		source.ResolveLink(mControllers[i]);
	}
}
//----------------------------------------------------------------------------
void Controlledable::PostLink ()
{
	Componable::PostLink();
}
//----------------------------------------------------------------------------
bool Controlledable::Register (OutStream& target) const
{
	if (Componable::Register(target))
	{
		int numCtrls = (int)mControllers.size();
		for (int i=0; i<numCtrls; i++)
		{
			target.Register(mControllers[i]);
		}
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Controlledable::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Componable::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteBool(mIsSelfCtrled);

	int numCtrls = (int)mControllers.size();
	target.Write(numCtrls);
	for (int i=0; i<numCtrls; i++)
	{
		target.WritePointer(mControllers[i]);
	}

	PX2_END_DEBUG_STREAM_SAVE(Controlledable, target);
}
//----------------------------------------------------------------------------
int Controlledable::GetStreamingSize (Stream &stream) const
{
	int numCtrls = (int)mControllers.size();

	int size = Componable::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_BOOLSIZE(mIsSelfCtrled);

	size += sizeof(numCtrls);
	size += numCtrls*PX2_POINTERSIZE(mControllers[0]);
	return size;
}
//----------------------------------------------------------------------------