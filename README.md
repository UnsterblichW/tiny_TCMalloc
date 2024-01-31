# tiny_tsmalloc

简介：
1. 参考了Google的tsmalloc项目来实现一个简易的内存池，
2. 未支持多平台（仅支持windows），
3. TCMalloc是Google对C的 `Malloc()` 和C++ 的运算符`new`的定制实现，可用于C和C++代码中的内存分配。TCMalloc是一个快速的多线程Malloc实现。
---
参考项目：[Google tsmalloc](https://github.com/google/tcmalloc)

---
参考知识：
* [cnblogs的博客](https://www.cnblogs.com/jiujuan/p/13869547.html)
* [tsmalloc的官方技术介绍](https://github.com/google/tcmalloc/blob/master/docs/design.md)

---
项目运行平台：
IDE：Visual Studio 2022
System: Windows10 / 11

---
一些问题记录：

> Q: 为什么`ThreadCache`中单次只能申请不超过256KB的空间，这个256KB怎么来的？
A: 不太清楚，反正Google的tcmalloc里面的`Thread_Cache`也是这样限制的
