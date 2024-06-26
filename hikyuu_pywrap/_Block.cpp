/*
 * _Block.cpp
 *
 *  Created on: 2015年2月10日
 *      Author: fasiondog
 */

#include <hikyuu/serialization/Block_serialization.h>
#include "pybind_utils.h"

using namespace hku;
namespace py = pybind11;

#if defined(_MSC_VER)
#pragma warning(disable : 4267)
#endif

string (Block::*getCategory)() const = &Block::category;
void (Block::*setCategory)(const string&) = &Block::category;
string (Block::*getName)() const = &Block::name;
void (Block::*setName)(const string&) = &Block::name;

bool (Block::*add_1)(const Stock&) = &Block::add;
bool (Block::*add_2)(const string&) = &Block::add;
bool (Block::*remove_1)(const Stock&) = &Block::remove;
bool (Block::*remove_2)(const string&) = &Block::remove;

void export_Block(py::module& m) {
    py::class_<Block>(m, "Block", "板块类，可视为证券的容器")
      .def(py::init<>())
      .def(py::init<const string&, const string&>())
      .def(py::init<const Block&>())

      .def("__str__", to_py_str<Block>)
      .def("__repr__", to_py_str<Block>)

      .def_property("category", setCategory, getCategory, "板块所属分类")
      .def_property("name", getName, setName, "板块名称")

      .def("empty", &Block::empty, R"(empty(self)
    
    是否为空)")

      .def("add", add_1, R"(add(self, stock)

    加入指定的证券

    :param Stock stock: 待加入的证券
    :return: 是否成功加入
    :rtype: bool)",
           py::keep_alive<1, 2>())

      .def("add", add_2, R"(add(self, market_code)

    根据"市场简称证券代码"加入指定的证券

    :param str market_code: 市场简称证券代码
    :return: 是否成功加入
    :rtype: bool)",
           py::keep_alive<1, 2>())

      .def("remove", remove_1, R"(remove(self, stock)

    移除指定证券

    :param Stock stock: 指定的证券
    :return: 是否成功
    :rtype: bool)")

      .def("remove", remove_2, R"(remove(market_code)

    移除指定证券

    :param str market_code: 市场简称证券代码
    :return: True 成功 | False 失败
    :rtype: bool)")

      .def("clear", &Block::clear, "移除包含的所有证券")

      .def("__len__", &Block::size, "包含的证券数量")

      .def("__getitem__", &Block::get, R"(__getitem__(self, market_code)

    :param str market_code: 证券代码
    :return: Stock 实例)")

      .def(
        "__iter__",
        [](const Block& blk) {
            return py::make_iterator<py::return_value_policy::reference_internal, StockMapIterator,
                                     StockMapIterator, const Stock&>(blk.begin(), blk.end());
        },
        py::keep_alive<0, 1>())

        DEF_PICKLE(Block);
}
