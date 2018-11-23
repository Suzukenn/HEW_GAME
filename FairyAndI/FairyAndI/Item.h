#ifndef __ITEM_H_
#define __ITEM_H_

//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <memory>
#include "Base3Dobject.h"
#include "Main.h"
#include "Model.h"
#include "SideViewCamera.h"

#define MAX_ITEM	(15)

//�񋓌^��`
typedef enum {
	ITEM_FIRE,
	ITEM_ICE,
	MAX_ITEMTYPE
}ITEMTYPE;

//�������N���X�錾������//
class ITEM final : private BASE3DOBJECT
{
	private:
        std::unique_ptr<MODEL> Model;
        LPCTSTR Name;

	public:
        void Draw(void);
		HRESULT Initialize(LPCTSTR);
		void Uninitialize(void);
		void Update(void);
};
#endif