
#include "GlobalHeader.h"

class CPartAxisAttributeInterface : public sxsdk::attribute_interface
{
private:
	sxsdk::shade_interface &shade;

	CAxisData m_data;		// 属性情報.
	bool m_deleteAttr;		// 属性を削除する場合はtrue.

private:
	virtual int get_shade_version () const { return SHADE_BUILD_NUMBER; }
	virtual sx::uuid_class get_uuid (void * = 0) { return PART_AXIS_ATTRIBUTE_ID; }

	virtual void accepts_shape (bool &accept, void *) { accept = true; }

	// カスタム情報が選択された.
	virtual bool ask_shape (sxsdk::shape_class &shape, void * = 0);

	// ワイヤーフレームの描画.
	virtual void make_wireframe (sxsdk::shape_class &shape, const sxsdk::mat4 &mat, int view, int flags, void *aux=0);

	// -----------------------------------------------.
	//	ダイアログのイベント処理用.
	// -----------------------------------------------.
	// ダイアログの初期化.
	virtual void initialize_dialog (sxsdk::dialog_interface &d, void * = 0);

	// ダイアログのイベントを受け取る.
	virtual bool respond(sxsdk::dialog_interface &d, sxsdk::dialog_item_class &item, int action, void * = 0);

	// ダイアログのデータを設定する.
	virtual void load_dialog_data (sxsdk::dialog_interface &d, void * = 0);

	// 値の変更を保存するときに呼ばれる.
	virtual void save_dialog_data (sxsdk::dialog_interface &d, void * = 0);

public:
	CPartAxisAttributeInterface (sxsdk::shade_interface& shade);

	// プラグイン名をSXUL(text.sxul)より取得
	static const char *name(sxsdk::shade_interface *shade) { return shade->gettext("title"); }

};
