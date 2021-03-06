format PE console
include 'win32a.inc'
entry start

section 'data' data readable writeable

string db 'Enter number: ',0 ;������ ��� ������
string2 db 'Number must be from -1 to 1',0 ;������ ��� ������
string3 db 'Sqrt(%f+1)=%f ',0
scanf_float db '%f', 0 ;������ ��� ����� float
number dd ?;���������� ��� ��������� �����
out1 dq ? ;���������� ��� ������
out2 dq ?
accuracy dd 0.001;��������
F1 dd 0.5 ;���������
F2 dd 2.0
n dd ?;���������� �����

section 'text' code executable readable
start:
        push string
        call [printf]
        push number;��������� �����
        push scanf_float
        call [scanf]
                    ;������� ����������� ������� [-1,1]
        finit ;������ ������ � FPU, �������� ���������� �� �������� �� ������ �������
        fld [number];��������� �����
        fld1;�������� �������
        fcomip st1;���������� �����
        jae .ok1;���� ����� ������
        push string2;������� ��������� �� ������
        call [printf]
        jmp .g;�� ��������� ������ ���������
        .ok1:

        fld1;��������� ����� �� �������� �� ������ -1
        fchs
        fcomip st1
        jbe .ok2;���� ��� �� ������ ���������� ����� ������
        push string2
        call [printf];����� ������ � ����� �� ���������
        jmp .g
        .ok2:

        ;float func(float x){
              ;float g = x/2;
              ;float result = 1.0;
              ;int i = 1;
              ;while (fabs(g) > 0.001){
              ;      result += g;
              ;      g *= x * ((0.5 - i)) / (i + 1);
              ;      i++;
              ;}
              ;return result;
        ;}
        finit;��� ������ ������ � FPU
        fld [accuracy];��������� ��������
        fld [number];�������� ��������� �������� ��� g, ��������� x
        fdiv [F2];����� ��� �� 2
        fld1;��������� 1 ��� ���������� result
        mov [n],1;������ ������� ����� �� 1
        .loop:;������ �����
        fadd st0,st1;result += g;
        fld [number];��������� x
        fld [F1];��������� 0.5f
        fisub [n];�������� �� ���� i (0.5-i)
        fmulp st1,st0;�������� �� x (x*(0.5-i))
        fild [n];��� ��� ��������� i
        fld1;��������� 1
        faddp st1,st0;����������, �������� i+1
        fdivp st1,st0;����� ������������ �����, �������� x*(0.5-i)/(i+1)
        fmul st0,st2;�������� �� g
        fstp st2;��������� ���������� ������� � g
        inc [n];����������� ������� �����
        fld st1;�������� g
        fabs;�������� ��� ������
        fcomip st3;���������� ��� � ���������
        jae .loop;���� g ������ ��������, �������� ������
        fstp qword[out2];������� ����� � ����������
        fld [number];��������� number �� double
        fstp qword[out1]

        push dword[out2+4];�����
        push dword[out2]
        push dword[out1+4]
        push dword[out1]
        push string3
        call [printf]

        .g:
        call [getch];����
        push 0
        call [ExitProcess];���������� ���������

section '.idata' import data readable
    library kernel, 'kernel32.dll',\
            msvcrt, 'msvcrt.dll',\
            user32,'USER32.DLL'

include 'api\user32.inc'
include 'api\kernel32.inc'
    import kernel,\
           ExitProcess, 'ExitProcess',\
           HeapCreate,'HeapCreate',\
           HeapAlloc,'HeapAlloc'
  include 'api\kernel32.inc'
    import msvcrt,\
           printf, 'printf',\
           scanf, 'scanf',\
           getch, '_getch'

