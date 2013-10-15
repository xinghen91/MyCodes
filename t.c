#include "/usr/include/python2.7/Python.h"

void
deal_error(const char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(EXIT_FAILURE);
}

int
main()
{
	PyObject *p_name = NULL, *p_module = NULL, *p_dict = NULL,
		 *p_func = NULL;

	//初始化Python解释器
	//任何C与Python的交互都需要在最开始调用此函数
	Py_Initialize();
	if(!Py_IsInitialized()) {
		deal_error("Cannot init Python interpreter!");	
	}

	//执行简单的Python的命令
	//这里主要是在Python搜索文件的路径里加上当前路径
	//否则不能找到对应的文件，也就不能加载对应的模块
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

	//导入Python模块
	//对应的文件名，去掉py的后缀
	p_name = PyString_FromString("t");
	p_module = PyImport_Import(p_name);
	if(!p_module) {
		deal_error("Cannot load the module!");
	}

	//此函数获取模块中的函数列表
	p_dict = PyModule_GetDict(p_module);
	if(!p_dict) {
		deal_error("Cannot get the dict");
	}

	//查找函数的位置
	p_func = PyDict_GetItemString(p_dict, "hello");
	if(!p_func || !PyCallable_Check(p_func)) {
		deal_error("Cannot find the function");
	}

	//调用函数
	PyObject_CallObject(p_func, NULL);

	//指针的释放
	Py_DECREF(p_name);
	Py_DECREF(p_module);
	Py_DECREF(p_dict);
	Py_DECREF(p_func);

	//关闭Python
	Py_Finalize();
	return 0;
}

