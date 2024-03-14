/*
 *  Copyright (c) 2024 hikyuu.org
 *
 *  Created on: 2024-03-12
 *      Author: fasiondog
 */

#pragma once

#include "hikyuu/KData.h"
#include "hikyuu/indicator/Indicator.h"
#include "hikyuu/utilities/Parameter.h"

namespace hku {

/**
 * 合成多因子
 * @ingroup MultiFactor
 */
class HKU_API MultiFactorBase : public enable_shared_from_this<MultiFactorBase> {
    PARAMETER_SUPPORT

public:
    typedef Indicator::value_t value_t;

public:
    MultiFactorBase();
    MultiFactorBase(const string& name);
    MultiFactorBase(const IndicatorList& inds, const StockList& stks, const KQuery& query,
                    const Stock& ref_stk, const string& name, int ic_n);

    /** 获取名称 */
    const string& name() const {
        return m_name;
    }

    /** 设置名称 */
    void name(const string& name) {
        m_name = name;
    }

    const DatetimeList& getDatetimeList() const {
        return m_ref_dates;
    }

    /** 获取指定证券合成因子 */
    const Indicator& get(const Stock&);

    /**
     * 获取所有证券合成后的新因子，顺序与传入的证券组合相同
     */
    const IndicatorList& getAll() const {
        return m_all_factors;
    }

    /** 获取指定日期截面的所有因子值 */
    const vector<std::pair<Stock, value_t>>& get(const Datetime&);

    /** 获取合成因子的IC */
    Indicator getIC(int ndays);

    /** 获取合成因子的 ICIR */
    Indicator getICIR(int ic_n, int ir_n);

    /** 执行计算 */
    void calculate();

    typedef std::shared_ptr<MultiFactorBase> MultiFactorPtr;
    MultiFactorPtr clone();

    virtual MultiFactorPtr _clone() = 0;
    virtual IndicatorList _calculate(const vector<IndicatorList>&) = 0;

protected:
    vector<IndicatorList> _alignAllInds();
    void _buildCrossSession();  // 计算完成后创建截面索引
    IndicatorList _getAllReturns(int ndays) const;

protected:
    string m_name;
    IndicatorList m_inds;  // 输入的原始因子列表
    StockList m_stks;      // 证券组合
    Stock m_ref_stk;       // 指定的参考证券
    KQuery m_query;        // 计算的日期范围条件

    // 以下变量为计算后生成
    DatetimeList m_ref_dates;  // 依据参考证券和query计算的参考日期，合成因子和该日期对齐
    unordered_map<Stock, size_t> m_stk_map;  // 证券->合成后因子位置索引
    IndicatorList m_all_factors;             // 保存所有证券合成后的新因子
    unordered_map<Datetime, size_t> m_date_index;
    vector<vector<std::pair<Stock, value_t>>> m_stk_factor_by_date;
    Indicator m_ic;

private:
    std::mutex m_mutex;
    bool m_calculated{false};

//============================================
// 序列化支持
//============================================
#if HKU_SUPPORT_SERIALIZATION
private:
    friend class boost::serialization::access;
    template <class Archive>
    void save(Archive& ar, const unsigned int version) const {
        ar& BOOST_SERIALIZATION_NVP(m_name);
        ar& BOOST_SERIALIZATION_NVP(m_inds);
        ar& BOOST_SERIALIZATION_NVP(m_stks);
        ar& BOOST_SERIALIZATION_NVP(m_ref_stk);
        ar& BOOST_SERIALIZATION_NVP(m_query);
        ar& BOOST_SERIALIZATION_NVP(m_ref_dates);
        ar& BOOST_SERIALIZATION_NVP(m_stk_map);
        ar& BOOST_SERIALIZATION_NVP(m_all_factors);
        ar& BOOST_SERIALIZATION_NVP(m_date_index);
        ar& BOOST_SERIALIZATION_NVP(m_stk_factor_by_date);
        ar& BOOST_SERIALIZATION_NVP(m_ic);
    }

    template <class Archive>
    void load(Archive& ar, const unsigned int version) {
        ar& BOOST_SERIALIZATION_NVP(m_name);
        ar& BOOST_SERIALIZATION_NVP(m_inds);
        ar& BOOST_SERIALIZATION_NVP(m_stks);
        ar& BOOST_SERIALIZATION_NVP(m_ref_stk);
        ar& BOOST_SERIALIZATION_NVP(m_query);
        ar& BOOST_SERIALIZATION_NVP(m_ref_dates);
        ar& BOOST_SERIALIZATION_NVP(m_stk_map);
        ar& BOOST_SERIALIZATION_NVP(m_all_factors);
        ar& BOOST_SERIALIZATION_NVP(m_date_index);
        ar& BOOST_SERIALIZATION_NVP(m_stk_factor_by_date);
        ar& BOOST_SERIALIZATION_NVP(m_ic);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
#endif /* HKU_SUPPORT_SERIALIZATION */
};

#if HKU_SUPPORT_SERIALIZATION
BOOST_SERIALIZATION_ASSUME_ABSTRACT(MultiFactorBase)
#endif

#if HKU_SUPPORT_SERIALIZATION
/**
 * 对于没有私有变量的继承子类，可直接使用该宏定义序列化
 * @code
 * class Drived: public MultiFactorBase {
 *     MULTIFACTOR_NO_PRIVATE_MEMBER_SERIALIZATION
 *
 * public:
 *     Drived();
 *     ...
 * };
 * @endcode
 * @ingroup MultiFactor
 */
#define MULTIFACTOR_NO_PRIVATE_MEMBER_SERIALIZATION               \
private:                                                          \
    friend class boost::serialization::access;                    \
    template <class Archive>                                      \
    void serialize(Archive& ar, const unsigned int version) {     \
        ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(MultiFactorBase); \
    }
#else
#define MULTIFACTOR_NO_PRIVATE_MEMBER_SERIALIZATION
#endif

typedef std::shared_ptr<MultiFactorBase> FactorPtr;
typedef std::shared_ptr<MultiFactorBase> MultiFactorPtr;
typedef std::shared_ptr<MultiFactorBase> MFPtr;

#define MULTIFACTOR_IMP(classname)             \
public:                                        \
    virtual MultiFactorPtr _clone() override { \
        return std::make_shared<classname>();  \
    }                                          \
    virtual IndicatorList _calculate(const vector<IndicatorList>&) override;

}  // namespace hku