/**
 * 選択形状のパートの座標軸を表示する.
 */

#include "GlobalHeader.h"
#include "PartAxisAttributeInterface.h"

//**************************************************//
//	グローバル関数									//
//**************************************************//
/**
 * プラグインインターフェースの生成.
 */
extern "C" SXSDKEXPORT void STDCALL create_interface (const IID &iid, int i, void **p, sxsdk::shade_interface *shade, void *) {
	unknown_interface *u = NULL;
	
	if (iid == attribute_iid) {
		if (i == 0) {
			u = new CPartAxisAttributeInterface(*shade);
		}
	}

	if (u) {
		u->AddRef();
		*p = (void *)u;
	}
}

/**
 * インターフェースの数を返す.
 */
extern "C" SXSDKEXPORT int STDCALL has_interface (const IID &iid, sxsdk::shade_interface *shade) {

	if (iid == attribute_iid) return 1;

	return 0;
}

/**
 * インターフェース名を返す.
 */
extern "C" SXSDKEXPORT const char * STDCALL get_name (const IID &iid, int i, sxsdk::shade_interface *shade, void *) {
	if (iid == attribute_iid) {
		if (i == 0) {
			return CPartAxisAttributeInterface::name(shade);
		}
	}

	return 0;
}

/**
 * プラグインのUUIDを返す.
 */
extern "C" SXSDKEXPORT sx::uuid_class STDCALL get_uuid (const IID &iid, int i, void *) {
	if (iid == attribute_iid) {
		if (i == 0) {
			return PART_AXIS_ATTRIBUTE_ID;
		}
	}

	return sx::uuid_class(0, 0, 0, 0);
}

/**
 * バージョン情報.
 */
extern "C" SXSDKEXPORT void STDCALL get_info (sxsdk::shade_plugin_info &info, sxsdk::shade_interface *shade, void *) {
	info.sdk_version = SHADE_BUILD_NUMBER;
	info.recommended_shade_version = 410000;
	info.major_version = 1;
	info.minor_version = 0;
	info.micro_version = 0;
	info.build_number =  0;
}

/**
 * 常駐プラグイン.
 */
extern "C" SXSDKEXPORT bool STDCALL is_resident (const IID &iid, int i, void *) {
	return true;
}

