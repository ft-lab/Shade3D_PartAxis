
#include "GlobalHeader.h"

class CPartAxisAttributeInterface : public sxsdk::attribute_interface
{
private:
	sxsdk::shade_interface &shade;

	CAxisData m_data;		// �������.
	bool m_deleteAttr;		// �������폜����ꍇ��true.

private:
	virtual int get_shade_version () const { return SHADE_BUILD_NUMBER; }
	virtual sx::uuid_class get_uuid (void * = 0) { return PART_AXIS_ATTRIBUTE_ID; }

	virtual void accepts_shape (bool &accept, void *) { accept = true; }

	// �J�X�^����񂪑I�����ꂽ.
	virtual bool ask_shape (sxsdk::shape_class &shape, void * = 0);

	// ���C���[�t���[���̕`��.
	virtual void make_wireframe (sxsdk::shape_class &shape, const sxsdk::mat4 &mat, int view, int flags, void *aux=0);

	// -----------------------------------------------.
	//	�_�C�A���O�̃C�x���g�����p.
	// -----------------------------------------------.
	// �_�C�A���O�̏�����.
	virtual void initialize_dialog (sxsdk::dialog_interface &d, void * = 0);

	// �_�C�A���O�̃C�x���g���󂯎��.
	virtual bool respond(sxsdk::dialog_interface &d, sxsdk::dialog_item_class &item, int action, void * = 0);

	// �_�C�A���O�̃f�[�^��ݒ肷��.
	virtual void load_dialog_data (sxsdk::dialog_interface &d, void * = 0);

	// �l�̕ύX��ۑ�����Ƃ��ɌĂ΂��.
	virtual void save_dialog_data (sxsdk::dialog_interface &d, void * = 0);

public:
	CPartAxisAttributeInterface (sxsdk::shade_interface& shade);

	// �v���O�C������SXUL(text.sxul)���擾
	static const char *name(sxsdk::shade_interface *shade) { return shade->gettext("title"); }

};
