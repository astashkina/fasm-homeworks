;Асташкина Мария, Вариант 2
;
;Разработать программу на FASM, которая вводит одномерный массив A[N],
;формирует из элементов массива A новый массив B из элементов из A,
;значение которых не совпадает с первым и последним элементами A.
;Память под массивы может выделяться как статически, так и динамически по выбору разработчика.
;
;Разбить решение задачи на функции следующим образом:
;        1       Ввод и вывод массивов оформить как подпрограммы.
;        2    Организовать вывод как исходного, так и сформированного массивов

format PE console

include 'win32a.inc'

entry start

section 'text' code executable readable

start:
        call SetArrA

        call ReserveArrB

        call GetElements

        call ExecuteOper

        call Output

        call Stop
        ret



SetArrA:
        cinvoke printf,str1

        cinvoke scanf,integer,sizeone

        mov eax,[sizeone]
        shl eax,2
        cinvoke malloc,eax

        mov [A],eax
        ret

ReserveArrB:
        mov eax,[sizeone]
        shl eax,2
        sub eax,8
        invoke malloc,eax
        add esp,4
        mov [B],eax
        ret

GetElements:

        mov edx,[A]
        mov ecx,[sizeone]
        lop:
                pusha
                cinvoke scanf,integer,edx
                popa

        add edx,4
        dec ecx
        jnz lop
        ret

ExecuteOper:
        mov eax,[A]
        mov ebx,[eax]
        mov [first],ebx
        mov ebx,[sizeone]
        dec ebx
        shl ebx,2
        add eax,ebx
        mov ebx,[eax]
        mov [last],ebx

        mov eax,[A]
        mov ebx,[first]
        mov edx,[last]
        mov ecx,[sizeone]
        mov edi,[B]

        add eax,4
        sub ecx,2

        lop2:
                mov esi,[eax]
                cmp esi,ebx
                je skip
                cmp esi,edx
                je skip
                        mov [edi],esi
                        add edi,4
                        inc [sizetwo]
                skip:
        add eax,4
        dec ecx
        jnz lop2
        ret

Output:

        mov eax,[B]
        mov ecx,[sizetwo]

        lop3:
                pusha
                cinvoke printf,integer2,[eax]
                popa

        add eax,4
        dec ecx
        jnz lop3
        ret

Stop:
        cinvoke scanf,integer,sizeone

        ret


section 'data' data readable writeable

sizeone dd ?
sizetwo dd ?

first dd ?
last dd ?

A dd ?
B dd ?
str1 db 'Set size of array:',13,10,0

integer db '%d',0
integer2 db ' %d',0

section 'imp' import readable

library msvcrt,'msvcrt.dll'

import msvcrt,\
       printf,'printf',\
       scanf,'scanf',\
       malloc,'malloc'


