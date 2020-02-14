
#include "PartAxisAttributeInterface.h"
#include "StreamCtrl.h"

enum {
	dlg_show_axis_id = 101,					// 軸を表示.
	dlg_shear_and_scale_id = 102,			// せん断とスケールを反映.
	dlg_axis_length_id = 103,				// 軸の長さ.
	dlg_delete_but_id = 104,				// 属性削除ボタン.
};

CPartAxisAttributeInterface::CPartAxisAttributeInterface (sxsdk::shade_interface& shade) : shade(shade)
{
}

/*
 * カスタム情報が選択された.
 */
bool CPartAxisAttributeInterface::ask_shape (sxsdk::shape_class &shape, void *)
{
	compointer<sxsdk::dialog_interface> dlg(shade.create_dialog_interface_with_uuid(PART_AXIS_ATTRIBUTE_ID));
	dlg->set_resource_name("part_axis_dlg");
	dlg->set_responder(this);
	this->AddRef();			// set_responder()に合わせて、参照カウンタを増やす。 .

	StreamCtrl::loadAxisData(shape, m_data);
	m_deleteAttr = false;

	// ダイアログの表示.
	if (dlg->ask()) {
		try {
			compointer<sxsdk::scene_interface> scene(shape.get_scene_interface());
			const int aCou = scene->get_number_of_active_shapes();
			for (int i = 0; i < aCou; ++i) {
				sxsdk::shape_class& pS = scene->active_shape(i);
				StreamCtrl::saveAxisData(pS, m_data);
			}
		} catch (...) { }
	}

	// 属性削除.
	if (m_deleteAttr) {
		try {
			compointer<sxsdk::scene_interface> scene(shape.get_scene_interface());
			const int aCou = scene->get_number_of_active_shapes();
			for (int i = 0; i < aCou; ++i) {
				sxsdk::shape_class& pS = scene->active_shape(i);
				StreamCtrl::removeAxisData(pS);
			}
		} catch (...) { }
	}

	return true;
}

/**
 * ワイヤーフレームの描画.
 */
void CPartAxisAttributeInterface::make_wireframe (sxsdk::shape_class &shape, const sxsdk::mat4 &mat, int view, int flags, void *)
{
	// streamより情報を取得.
	CAxisData axisD;
	StreamCtrl::loadAxisData(shape, axisD);
	if (!axisD.showAxis) return;

	sxsdk::mat4 m = shape.get_transformation();

	// 変換行列のせん断とスケールをリセット.
	if (!m_data.shearAndScale) {
		sxsdk::vec3 scale, shear, rotate, translate;
		m.unmatrix(scale, shear, rotate, translate);
		m = sxsdk::mat4::rotate(rotate) * sxsdk::mat4::translate(translate);
	}

	sxsdk::vec3 pA[2];

	{
		shade.set_wireframe_color_obsolete(sxsdk::rgb_class(1, 0, 0));
		pA[0] = sxsdk::vec3(0, 0, 0);
		pA[1] = sxsdk::vec3(axisD.axisLength, 0, 0);
		shape.make_line_wireframe(m, 2, pA);
	}
	{
		shade.set_wireframe_color_obsolete(sxsdk::rgb_class(0, 1, 0));
		pA[0] = sxsdk::vec3(0, 0, 0);
		pA[1] = sxsdk::vec3(0, axisD.axisLength, 0);
		shape.make_line_wireframe(m, 2, pA);
	}
	{
		shade.set_wireframe_color_obsolete(sxsdk::rgb_class(0, 0, 1));
		pA[0] = sxsdk::vec3(0, 0, 0);
		pA[1] = sxsdk::vec3(0, 0, axisD.axisLength);
		shape.make_line_wireframe(m, 2, pA);
	}
}

// -----------------------------------------------.
//	ダイアログのイベント処理用.
// -----------------------------------------------.
// ダイアログの初期化.
void CPartAxisAttributeInterface::initialize_dialog (sxsdk::dialog_interface &d, void *)
{
}

// ダイアログのイベントを受け取る.
bool CPartAxisAttributeInterface::respond (sxsdk::dialog_interface &d, sxsdk::dialog_item_class &item, int action, void *)
{
	const int id = item.get_id();		// アクションがあったダイアログアイテムのID.

	if (id == sx::iddefault) {
		m_data.clear();
		load_dialog_data(d);
		return true;
	}
	if (id == dlg_delete_but_id) {
		m_deleteAttr = true;
		return false;			// ダイアログボックスを閉じるためにfalseにする.
	}

	if (id == dlg_show_axis_id) {
		m_data.showAxis = item.get_bool();
		return true;
	}
	if (id == dlg_shear_and_scale_id) {
		m_data.shearAndScale = item.get_bool();
		return true;
	}
	if (id == dlg_axis_length_id) {
		m_data.axisLength = item.get_float();
		return true;
	}

	return false;
}

// ダイアログのデータを設定する.
void CPartAxisAttributeInterface::load_dialog_data (sxsdk::dialog_interface &d, void *)
{
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_show_axis_id));
		item->set_bool(m_data.showAxis);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_shear_and_scale_id));
		item->set_bool(m_data.shearAndScale);
	}
	{
		sxsdk::dialog_item_class* item;
		item = &(d.get_dialog_item(dlg_axis_length_id));
		item->set_float(m_data.axisLength);
	}
}

// 値の変更を保存するときに呼ばれる.
void CPartAxisAttributeInterface::save_dialog_data (sxsdk::dialog_interface &d, void *)
{
}

