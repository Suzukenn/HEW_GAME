#ifndef _MOUSE_H_
#define _MOUSE_H_

//�������񋓌^��`������//
typedef enum
{
    MOUSEBUTTON_LEFT,
    MOUSEBUTTON_RIGHT,
    MOUSEBUTTON_CENTER,
    MOUSEBUTTON_MAX
}MOUSEBUTTON;

//�������N���X�錾������//
class MOUSE
{
    private:
        LPDIRECTINPUTDEVICE8 Device; //�f�o�C�X
        POINT Position;              //�J�[�\�����W
        DIMOUSESTATE Current;	     //���݂̏��
        DIMOUSESTATE Preview;	     //�O��̏��
        DIMOUSESTATE Trigger;	     //�g���K���
        DIMOUSESTATE Release;	     //�����[�X���
        HWND Handle;                 //�E�B���h�E�n���h��

    public:
        HRESULT Initialize(HWND, LPDIRECTINPUT8);
        void Uninitialize(void);
        void Update(void);

        bool GetHold(MOUSEBUTTON);
        POINT GetCursor(void);
        bool GetRelease(MOUSEBUTTON);
        bool GetTrigger(MOUSEBUTTON);
};

#endif