/**
 *  @file   GlobalHeader.h
 *  @brief  共通して使用する変数など.
 */

#ifndef _GLOBALHEADER_H
#define _GLOBALHEADER_H

#include "sxsdk.cxx"

/**
 * インターフェイス派生クラスのプラグインID.
 */
#define PART_AXIS_ATTRIBUTE_ID sx::uuid_class("3AE600F7-EAC1-45BF-9BB8-17EABB53E1C5")

// streamに保存するバージョン.
#define AXIS_STREAM_VERSION  0x100

/**
 * attribute情報.
 */
class CAxisData
{
public:
	bool showAxis;				// 軸を表示.
	bool shearAndScale;			// せん断とスケールを反映.
	float axisLength;			// 軸の長さ.

public:
	CAxisData () {
		clear();
	}
	~CAxisData () { }

	void clear () {
		showAxis = false;
		shearAndScale = false;
		axisLength = 100.0f;
	}

	CAxisData (const CAxisData& v) {
		this->showAxis = v.showAxis;
		this->shearAndScale = v.shearAndScale;
		this->axisLength = v.axisLength;
	}

    CAxisData& operator = (const CAxisData &v) {
		this->showAxis = v.showAxis;
		this->shearAndScale = v.shearAndScale;
		this->axisLength = v.axisLength;
		return (*this);
	}
};

#endif
