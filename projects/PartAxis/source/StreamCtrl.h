/**
 * streamへの入出力.
 */

#ifndef _STREAMCTRL_H
#define _STREAMCTRL_H

#include "GlobalHeader.h"

namespace StreamCtrl
{
	/**
	 * Axis情報を保存/読み込み.
	 */
	void saveAxisData (sxsdk::shape_class& shape, const CAxisData& data);
	void loadAxisData (sxsdk::shape_class& shape, CAxisData& data);

	/**
	 * Axis情報を削除.
	 */
	void removeAxisData (sxsdk::shape_class& shape);
}

#endif
