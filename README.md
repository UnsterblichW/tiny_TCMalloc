# tiny_tsmalloc

��飺
1. �ο���Google��tsmalloc��Ŀ��ʵ��һ�����׵��ڴ�أ�
2. δ֧�ֶ�ƽ̨����֧��windows����
3. TCMalloc��Google��C�� `Malloc()` ��C++ �������`new`�Ķ���ʵ�֣�������C��C++�����е��ڴ���䡣TCMalloc��һ�����ٵĶ��߳�Mallocʵ�֡�
---
�ο���Ŀ��[Google tsmalloc](https://github.com/google/tcmalloc)

---
�ο�֪ʶ��
* [cnblogs�Ĳ���](https://www.cnblogs.com/jiujuan/p/13869547.html)
* [tsmalloc�Ĺٷ���������](https://github.com/google/tcmalloc/blob/master/docs/design.md)

---
��Ŀ����ƽ̨��
IDE��Visual Studio 2022
System: Windows10 / 11

---
һЩ�����¼��

> Q: Ϊʲô`ThreadCache`�е���ֻ�����벻����256KB�Ŀռ䣬���256KB��ô���ģ�
A: ��̫���������Google��tcmalloc�����`Thread_Cache`Ҳ���������Ƶ�
