/**
 * streamへの入出力.
 */
#include "StreamCtrl.h"

#include <string>
#include <algorithm>
#include <iostream>

/**
 * Axis情報を削除.
 */
void StreamCtrl::removeAxisData (sxsdk::shape_class& shape)
{
	try {
		shape.delete_attribute_with_uuid(PART_AXIS_ATTRIBUTE_ID);
	} catch (...) { }
}

/**
 * Axis情報を保存/読み込み.
 */
void StreamCtrl::saveAxisData (sxsdk::shape_class& shape, const CAxisData& data)
{
	try {
		compointer<sxsdk::stream_interface> stream(shape.create_attribute_stream_interface_with_uuid(PART_AXIS_ATTRIBUTE_ID, PART_AXIS_ATTRIBUTE_ID));
		if (!stream) return;
		stream->set_pointer(0);
		stream->set_size(0);

		int iDat;
		int iVersion = AXIS_STREAM_VERSION;
		stream->write_int(iVersion);

		iDat = data.showAxis ? 1 : 0;
		stream->write_int(iDat);

		iDat = data.shearAndScale ? 1 : 0;
		stream->write_int(iDat);

		stream->write_float(data.axisLength);

		if (data.showAxis) stream->set_label("[Show Axis]");
		else stream->set_label("[Hide Axis]");

	} catch (...) { }
}

void StreamCtrl::loadAxisData (sxsdk::shape_class& shape, CAxisData& data)
{
	data.clear();
	try {
		compointer<sxsdk::stream_interface> stream(shape.get_attribute_stream_interface_with_uuid(PART_AXIS_ATTRIBUTE_ID));
		if (!stream) return;
		stream->set_pointer(0);

		int iDat;
		int iVersion;
		stream->read_int(iVersion);

		stream->read_int(iDat);
		data.showAxis = (iDat != 0) ? true : false;

		stream->read_int(iDat);
		data.shearAndScale = (iDat != 0) ? true : false;

		stream->read_float(data.axisLength);
	} catch (...) { }
}
