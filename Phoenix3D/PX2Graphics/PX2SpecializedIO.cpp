/*
*
* �ļ�����	��	PX2SpecializedIO.cpp
*
*/

#include "PX2SpecializedIO.hpp"

namespace PX2
{
//----------------------------------------------------------------------------
// Bound
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (Bound& datum)
{
	APoint center;
	float radius;
	if (!ReadAggregate(center) || !Read(radius))
	{
		return false;
	}

	datum.SetCenter(center);
	datum.SetRadius(radius);
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, Bound* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, Bound*& data)
{
	if (numElements > 0)
	{
		data = new1<Bound>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, Bound*& data)
{
	if (!Read(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		data = new1<Bound>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const Bound& datum)
{
	APoint center = datum.GetCenter();
	float radius = datum.GetRadius();
	return WriteAggregate(center) && Write(radius);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const Bound* data)
{
	if (!Write(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const Bound* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Float1
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (Float1& datum)
{
	return ReadVV(1, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, Float1* data)
{
	return ReadVV(numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, Float1*& data)
{
	if (numElements > 0)
	{
		data = new1<Float1>(numElements);
		return ReadVV(numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, Float1*& data)
{
	if (!Read(numElements))
	{
		numElements = 0;
		data = 0;
		return false;
	}

	if (numElements > 0)
	{
		data = new1<Float1>(numElements);
		return ReadVV(numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const Float1& datum)
{
	return WriteN(1, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const Float1* data)
{
	return WriteW(numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const Float1* data)
{
	return WriteN(numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Float2
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (Float2& datum)
{
	return ReadVV(2, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, Float2* data)
{
	return ReadVV(2*numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, Float2*& data)
{
	if (numElements > 0)
	{
		data = new1<Float2>(numElements);
		return ReadVV(2*numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, Float2*& data)
{
	int rawNumElements;
	if (!Read(rawNumElements))
	{
		numElements = 0;
		data = 0;
		return false;
	}

	numElements = rawNumElements/2;
	if (numElements > 0)
	{
		data = new1<Float2>(numElements);
		return ReadVV(rawNumElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const Float2& datum)
{
	return WriteN(2, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const Float2* data)
{
	return WriteW(2*numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const Float2* data)
{
	return WriteN(2*numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Float3
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (Float3& datum)
{
	return ReadVV(3, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, Float3* data)
{
	return ReadVV(3*numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, Float3*& data)
{
	if (numElements > 0)
	{
		data = new1<Float3>(numElements);
		return ReadVV(3*numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, Float3*& data)
{
	int rawNumElements;
	if (!Read(rawNumElements))
	{
		numElements = 0;
		data = 0;
		return false;
	}

	numElements = rawNumElements/3;
	if (numElements > 0)
	{
		data = new1<Float3>(numElements);
		return ReadVV(rawNumElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const Float3& datum)
{
	return WriteN(3, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const Float3* data)
{
	return WriteW(3*numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const Float3* data)
{
	return WriteN(3*numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Float4
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (Float4& datum)
{
	return ReadVV(4, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, Float4* data)
{
	return ReadVV(4*numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, Float4*& data)
{
	if (numElements > 0)
	{
		data = new1<Float4>(numElements);
		return ReadVV(4*numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, Float4*& data)
{
	int rawNumElements;
	if (!Read(rawNumElements))
	{
		numElements = 0;
		data = 0;
		return false;
	}

	numElements = rawNumElements/4;
	if (numElements > 0)
	{
		data = new1<Float4>(numElements);
		return ReadVV(rawNumElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const Float4& datum)
{
	return WriteN(4, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const Float4* data)
{
	return WriteW(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const Float4* data)
{
	return WriteN(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// HMatrix
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (HMatrix& datum)
{
	return ReadVV(16, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, HMatrix* data)
{
	return ReadVV(16*numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, HMatrix*& data)
{
	if (numElements > 0)
	{
		data = new1<HMatrix>(numElements);
		return ReadVV(16*numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, HMatrix*& data)
{
	int rawNumElements;
	if (!Read(rawNumElements))
	{
		numElements = 0;
		data = 0;
		return false;
	}

	numElements = rawNumElements/16;
	if (numElements > 0)
	{
		data = new1<HMatrix>(numElements);
		return ReadVV(rawNumElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const HMatrix& datum)
{
	return WriteN(16, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const HMatrix* data)
{
	return WriteW(16*numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const HMatrix* data)
{
	return WriteN(16*numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// HPlane
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (HPlane& datum)
{
	return ReadVV(4, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, HPlane* data)
{
	return ReadVV(4*numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, HPlane*& data)
{
	if (numElements > 0)
	{
		data = new1<HPlane>(numElements);
		return ReadVV(4*numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, HPlane*& data)
{
	int rawNumElements;
	if (!Read(rawNumElements))
	{
		numElements = 0;
		data = 0;
		return false;
	}

	numElements = rawNumElements/4;
	if (numElements > 0)
	{
		data = new1<HPlane>(numElements);
		return ReadVV(rawNumElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const HPlane& datum)
{
	return WriteN(4, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const HPlane* data)
{
	return WriteW(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const HPlane* data)
{
	return WriteN(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// APoint
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (APoint& datum)
{
	return ReadVV(4, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, APoint* data)
{
	return ReadVV(4*numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, APoint*& data)
{
	if (numElements > 0)
	{
		data = new1<APoint>(numElements);
		return ReadVV(4*numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, APoint*& data)
{
	int rawNumElements;
	if (!Read(rawNumElements))
	{
		numElements = 0;
		data = 0;
		return false;
	}

	numElements = rawNumElements/4;
	if (numElements > 0)
	{
		data = new1<APoint>(numElements);
		return ReadVV(rawNumElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const APoint& datum)
{
	return WriteN(4, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const APoint* data)
{
	return WriteW(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const APoint* data)
{
	return WriteN(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// AVector
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (AVector& datum)
{
	return ReadVV(4, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, AVector* data)
{
	return ReadVV(4*numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, AVector*& data)
{
	if (numElements > 0)
	{
		data = new1<AVector>(numElements);
		return ReadVV(4*numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, AVector*& data)
{
	int rawNumElements;
	if (!Read(rawNumElements))
	{
		numElements = 0;
		data = 0;
		return false;
	}

	numElements = rawNumElements/4;
	if (numElements > 0)
	{
		data = new1<AVector>(numElements);
		return ReadVV(rawNumElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const AVector& datum)
{
	return WriteN(4, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const AVector* data)
{
	return WriteW(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const AVector* data)
{
	return WriteN(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// HQuaternion
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (HQuaternion& datum)
{
	return ReadVV(4, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, HQuaternion* data)
{
	return ReadVV(4*numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, HQuaternion*& data)
{
	if (numElements > 0)
	{
		data = new1<HQuaternion>(numElements);
		return ReadVV(4*numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, HQuaternion*& data)
{
	int rawNumElements;
	if (!Read(rawNumElements))
	{
		numElements = 0;
		data = 0;
		return false;
	}

	numElements = rawNumElements/4;
	if (numElements > 0)
	{
		data = new1<HQuaternion>(numElements);
		return ReadVV(rawNumElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const HQuaternion& datum)
{
	return WriteN(4, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const HQuaternion* data)
{
	return WriteW(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const HQuaternion* data)
{
	return WriteN(4*numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Transform
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (Transform& datum)
{
	return ReadAggregate(datum.mHMatrix)
		&& ReadAggregate(datum.mInvHMatrix)
		&& ReadAggregate(datum.mMatrix)
		&& ReadAggregate(datum.mTranslate)
		&& ReadAggregate(datum.mScale)
		&& ReadBool(datum.mIsIdentity)
		&& ReadBool(datum.mIsRSMatrix)
		&& ReadBool(datum.mIsUniformScale)
		&& ReadBool(datum.mInverseNeedsUpdate);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, Transform* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, Transform*& data)
{
	if (numElements > 0)
	{
		data = new1<Transform>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, Transform*& data)
{
	if (!Read(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		data = new1<Transform>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const Transform& datum)
{
	return WriteAggregate(datum.mHMatrix)
		&& WriteAggregate(datum.mInvHMatrix)
		&& WriteAggregate(datum.mMatrix)
		&& WriteAggregate(datum.mTranslate)
		&& WriteAggregate(datum.mScale)
		&& WriteBool(datum.mIsIdentity)
		&& WriteBool(datum.mIsRSMatrix)
		&& WriteBool(datum.mIsUniformScale)
		&& WriteBool(datum.mInverseNeedsUpdate);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const Transform* data)
{
	if (!Write(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const Transform* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Vector3f
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (Vector3f& datum)
{
	return ReadVV(3, (float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, Vector3f* data)
{
	return ReadVV(3*numElements, (float*)data);
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, Vector3f*& data)
{
	if (numElements > 0)
	{
		data = new1<Vector3f>(numElements);
		return ReadVV(3*numElements, (float*)data);
	}
	data = 0;
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, Vector3f*& data)
{
	int rawNumElements;
	if (ReadRR(rawNumElements, (float*&)data))
	{
		numElements = rawNumElements/3;
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregate (const Vector3f& datum)
{
	return WriteN(3, (const float*)datum);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const Vector3f* data)
{
	return WriteW(3*numElements, (const float*)data);
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const Vector3f* data)
{
	return WriteN(3*numElements, (const float*)data);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Sizef
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregate (Sizef& datum)
{
	if (!Read(datum.Width))
		return false;

	if (!Read(datum.Height))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregateVV (int numElements, Sizef *data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, Sizef *&data)
{
	if (numElements > 0)
	{
		data = new1<Sizef>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int &numElements, Sizef *&data)
{
	if (!Read(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		data = new1<Sizef>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregate (const Sizef& datum)
{
	if (!Write(datum.Width))
		return false;

	if (!Write(datum.Height))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const Sizef* data)
{
	if (!Write(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregateN (int numElements, const Sizef* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Rectf
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregate (Rectf& datum)
{
	if (!Read(datum.Left))
		return false;

	if (!Read(datum.Bottom))
		return false;

	if (!Read(datum.Right))
		return false;

	if (!Read(datum.Top))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregateVV (int numElements, Rectf *data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, Rectf *&data)
{
	if (numElements > 0)
	{
		data = new1<Rectf>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int &numElements, Rectf *&data)
{
	if (!Read(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		data = new1<Rectf>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregate (const Rectf& datum)
{
	if (!Write(datum.Left))
		return false;

	if (!Write(datum.Bottom))
		return false;

	if (!Write(datum.Right))
		return false;

	if (!Write(datum.Top))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateW (int numElements, const Rectf* data)
{
	if (!Write(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregateN (int numElements, const Rectf* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// InterpCurvePointFloat
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (InterpCurvePointFloat& datum)
{
	if (!Read(datum.InVal))
		return false;

	if (!Read(datum.OutVal))
		return false;

	if (!Read(datum.ArriveTangent))
		return false;

	if (!Read(datum.LeaveTangent))
		return false;

	if (!ReadEnum(datum.InterpMode))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements, InterpCurvePointFloat* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, InterpCurvePointFloat*& data)
{
	if (numElements > 0)
	{
		data = new1<InterpCurvePointFloat>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, 
	InterpCurvePointFloat*& data)
{
	if (!Read(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		data = new1<InterpCurvePointFloat>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregate (const InterpCurvePointFloat& datum)
{
	if (!Write(datum.InVal))
		return false;

	if (!Write(datum.OutVal))
		return false;

	if (!Write(datum.ArriveTangent))
		return false;

	if (!Write(datum.LeaveTangent))
		return false;

	if (!WriteEnum(datum.InterpMode))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregateW (int numElements, 
	const InterpCurvePointFloat* data)
{
	if (!Write(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregateN (int numElements, 
	const InterpCurvePointFloat* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// InterpCurvePointFloat3
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregate (InterpCurvePointFloat3& datum)
{
	if (!Read(datum.InVal))
		return false;

	if (!ReadAggregate(datum.OutVal))
		return false;

	if (!ReadAggregate(datum.ArriveTangent))
		return false;

	if (!ReadAggregate(datum.LeaveTangent))
		return false;

	if (!ReadEnum(datum.InterpMode))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVV (int numElements,
	InterpCurvePointFloat3* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateVR (int numElements, 
	InterpCurvePointFloat3*& data)
{
	if (numElements > 0)
	{
		data = new1<InterpCurvePointFloat3>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, 
	InterpCurvePointFloat3*& data)
{
	if (!Read(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		data = new1<InterpCurvePointFloat3>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregate (const InterpCurvePointFloat3& datum)
{
	if (!Write(datum.InVal))
		return false;

	if (!WriteAggregate(datum.OutVal))
		return false;

	if (!WriteAggregate(datum.ArriveTangent))
		return false;

	if (!WriteAggregate(datum.LeaveTangent))
		return false;

	if (!WriteEnum(datum.InterpMode))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregateW (int numElements,
	const InterpCurvePointFloat3* data)
{
	if (!Write(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregateN (int numElements,
	const InterpCurvePointFloat3* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// InterpCurveFloat
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregate (InterpCurveFloat& datum)
{
	int numPoints = 0;
	if (!Read(numPoints))
		return false;

	if (numPoints > 0)
	{
		datum.Points.resize(numPoints);

		for (int i=0; i<numPoints; i++)
		{
			if (!ReadAggregate(datum.Points[i]))
				return false;
		}
	}

	if (!ReadEnum(datum.InterpMethod))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregateVV (int numElements, InterpCurveFloat* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregateVR (int numElements, InterpCurveFloat*& data)
{
	if (numElements > 0)
	{
		data = new1<InterpCurveFloat>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, InterpCurveFloat*& data)
{
	if (!Read(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		data = new1<InterpCurveFloat>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregate (const InterpCurveFloat& datum)
{
	int numPoints = (int)datum.Points.size();

	if (!Write(numPoints))
		return false;

	for (int i=0; i<numPoints; i++)
	{
		if (!WriteAggregate(datum.Points[i]))
			return false;
	}

	if (!WriteEnum(datum.InterpMethod))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregateW (int numElements, const InterpCurveFloat* data)
{
	if (!Write(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const InterpCurveFloat* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// InterpCurveFloat3
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregate (InterpCurveFloat3& datum)
{
	int numPoints = 0;
	if (!Read(numPoints))
		return false;

	if (numPoints > 0)
	{
		datum.Points.resize(numPoints);

		for (int i=0; i<numPoints; i++)
		{
			if (!ReadAggregate(datum.Points[i]))
				return false;
		}
	}

	if (!ReadEnum(datum.InterpMethod))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregateVV (int numElements, InterpCurveFloat3* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <> 
bool InStream::ReadAggregateVR (int numElements, InterpCurveFloat3*& data)
{
	if (numElements > 0)
	{
		data = new1<InterpCurveFloat3>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <>
bool InStream::ReadAggregateRR (int& numElements, InterpCurveFloat3*& data)
{
	if (!Read(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		data = new1<InterpCurveFloat3>(numElements);
		for (int i = 0; i < numElements; ++i)
		{
			if (!ReadAggregate(data[i]))
			{
				return false;
			}
		}
	}
	else
	{
		data = 0;
	}

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregate (const InterpCurveFloat3& datum)
{
	int numPoints = (int)datum.Points.size();

	if (!Write(numPoints))
		return false;

	for (int i=0; i<numPoints; i++)
	{
		if (!WriteAggregate(datum.Points[i]))
			return false;
	}

	if (!WriteEnum(datum.InterpMethod))
		return false;

	return true;
}
//----------------------------------------------------------------------------
template <> 
bool OutStream::WriteAggregateW (int numElements, const InterpCurveFloat3* data)
{
	if (!Write(numElements))
	{
		return false;
	}

	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------
template <>
bool OutStream::WriteAggregateN (int numElements, const InterpCurveFloat3* data)
{
	if (numElements > 0)
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (!WriteAggregate(data[i]))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------

}
