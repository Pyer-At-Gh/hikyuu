/*
 * ICos.cpp
 *
 *  Copyright (c) 2019 hikyuu.org
 *
 *  Created on: 2019-5-1
 *      Author: fasiondog
 */

#include "ICos.h"

#if HKU_SUPPORT_SERIALIZATION
BOOST_CLASS_EXPORT(hku::ICos)
#endif

namespace hku {

ICos::ICos() : IndicatorImp("COS", 1) {}

ICos::~ICos() {}

void ICos::_calculate(const Indicator &data) {
    size_t total = data.size();
    m_discard = data.discard();
    if (m_discard >= total) {
        m_discard = total;
        return;
    }

    auto const *src = data.data();
    auto *dst = this->data();
    for (size_t i = m_discard; i < total; ++i) {
        dst[i] = std::cos(src[i]);
    }
}

Indicator HKU_API COS() {
    return Indicator(make_shared<ICos>());
}

} /* namespace hku */
