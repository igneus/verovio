/////////////////////////////////////////////////////////////////////////////
// Name:        rend.cpp
// Author:      Laurent Pugin
// Created:     2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "rend.h"

//----------------------------------------------------------------------------

#include <cassert>

//----------------------------------------------------------------------------

#include "editorial.h"
#include "functor.h"
#include "lb.h"
#include "num.h"
#include "symbol.h"
#include "text.h"
#include "vrv.h"

namespace vrv {

//----------------------------------------------------------------------------
// Rend
//----------------------------------------------------------------------------

static const ClassRegistrar<Rend> s_factory("rend", REND);

Rend::Rend()
    : TextElement(REND, "rend-")
    , AreaPosInterface()
    , AttColor()
    , AttLang()
    , AttNNumberLike()
    , AttTextRendition()
    , AttTypography()
    , AttWhitespace()
{
    this->RegisterInterface(AreaPosInterface::GetAttClasses(), AreaPosInterface::IsInterface());
    this->RegisterAttClass(ATT_COLOR);
    this->RegisterAttClass(ATT_LANG);
    this->RegisterAttClass(ATT_NNUMBERLIKE);
    this->RegisterAttClass(ATT_TEXTRENDITION);
    this->RegisterAttClass(ATT_TYPOGRAPHY);
    this->RegisterAttClass(ATT_WHITESPACE);

    this->Reset();
}

Rend::~Rend() {}

void Rend::Reset()
{
    TextElement::Reset();
    AreaPosInterface::Reset();
    this->ResetColor();
    this->ResetLang();
    this->ResetNNumberLike();
    this->ResetTextRendition();
    this->ResetTypography();
    this->ResetWhitespace();
}

bool Rend::IsSupportedChild(Object *child)
{
    if (child->Is(LB)) {
        assert(dynamic_cast<Lb *>(child));
    }
    else if (child->Is(NUM)) {
        assert(dynamic_cast<Num *>(child));
    }
    else if (child->Is(REND)) {
        assert(dynamic_cast<Rend *>(child));
    }
    else if (child->Is(SYMBOL)) {
        assert(dynamic_cast<Symbol *>(child));
    }
    else if (child->Is(TEXT)) {
        assert(dynamic_cast<Text *>(child));
    }
    else if (child->IsEditorialElement()) {
        assert(dynamic_cast<EditorialElement *>(child));
    }
    else {
        return false;
    }
    return true;
}

bool Rend::HasEnclosure() const
{
    if (!this->HasRend()) return false;

    const bool hasEnclosure = ((this->GetRend() == TEXTRENDITION_box) || (this->GetRend() == TEXTRENDITION_circle)
        || (this->GetRend() == TEXTRENDITION_dbox) || (this->GetRend() == TEXTRENDITION_tbox));
    return hasEnclosure;
}

//----------------------------------------------------------------------------
// Functor methods
//----------------------------------------------------------------------------

FunctorCode Rend::Accept(Functor &functor)
{
    return functor.VisitRend(this);
}

FunctorCode Rend::Accept(ConstFunctor &functor) const
{
    return functor.VisitRend(this);
}

FunctorCode Rend::AcceptEnd(Functor &functor)
{
    return functor.VisitRendEnd(this);
}

FunctorCode Rend::AcceptEnd(ConstFunctor &functor) const
{
    return functor.VisitRendEnd(this);
}

} // namespace vrv
