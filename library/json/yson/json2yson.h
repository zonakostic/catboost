#pragma once

#include <library/json/json_reader.h>
#include <library/json/json_value.h>
#include <library/yson/writer.h>

namespace NJson2Yson {
    class TJsonBuilderImpl: public NYT::TYsonConsumerBase {
    public:
        TJsonBuilderImpl(NJson::TParserCallbacks* parserCallbacks)
            : ParserCallbacks_(parserCallbacks)
        {
        }

        void OnStringScalar(const TStringBuf& value) override {
            ParserCallbacks_->OnString(value);
        }

        void OnInt64Scalar(i64 value) override {
            ParserCallbacks_->OnInteger(value);
        }

        void OnUint64Scalar(ui64 value) override {
            ParserCallbacks_->OnUInteger(value);
        }

        void OnDoubleScalar(double value) override {
            ParserCallbacks_->OnDouble(value);
        }

        void OnBooleanScalar(bool value) override {
            ParserCallbacks_->OnBoolean(value);
        }

        void OnEntity() override {
            ParserCallbacks_->OnNull();
        }

        void OnBeginList() override {
            ParserCallbacks_->OnOpenArray();
        }

        void OnListItem() override {
        }

        void OnEndList() override {
            ParserCallbacks_->OnCloseArray();
        }

        void OnBeginMap() override {
            ParserCallbacks_->OnOpenMap();
        }

        void OnKeyedItem(const TStringBuf& key) override {
            ParserCallbacks_->OnMapKey(key);
        }

        void OnEndMap() override {
            ParserCallbacks_->OnCloseMap();
        }

        void OnBeginAttributes() override {
        }

        void OnEndAttributes() override {
        }

    private:
        NJson::TParserCallbacks* ParserCallbacks_;
    };

    template <typename TBase>
    class TSkipAttributesProxy: public TBase {
    public:
        TSkipAttributesProxy<TBase>() = default;

        TSkipAttributesProxy<TBase>(NJson::TParserCallbacks* parserCallbacks)
            : TBase(parserCallbacks)
        {
        }

        void OnStringScalar(const TStringBuf& value) override {
            if (AttributesDepth == 0) {
                TBase::OnStringScalar(value);
            }
        }

        void OnInt64Scalar(i64 value) override {
            if (AttributesDepth == 0) {
                TBase::OnInt64Scalar(value);
            }
        }

        void OnUint64Scalar(ui64 value) override {
            if (AttributesDepth == 0) {
                TBase::OnInt64Scalar(value);
            }
        }

        void OnDoubleScalar(double value) override {
            if (AttributesDepth == 0) {
                TBase::OnDoubleScalar(value);
            }
        }

        void OnBooleanScalar(bool value) override {
            if (AttributesDepth == 0) {
                TBase::OnBooleanScalar(value);
            }
        }

        void OnEntity() override {
            if (AttributesDepth == 0) {
                TBase::OnEntity();
            }
        }

        void OnBeginList() override {
            if (AttributesDepth == 0) {
                TBase::OnBeginList();
            }
        }

        void OnListItem() override {
            if (AttributesDepth == 0) {
                TBase::OnListItem();
            }
        }

        void OnEndList() override {
            if (AttributesDepth == 0) {
                TBase::OnEndList();
            }
        }

        void OnBeginMap() override {
            if (AttributesDepth == 0) {
                TBase::OnBeginMap();
            }
        }

        void OnKeyedItem(const TStringBuf& key) override {
            if (AttributesDepth == 0) {
                TBase::OnKeyedItem(key);
            }
        }

        void OnEndMap() override {
            if (AttributesDepth == 0) {
                TBase::OnEndMap();
            }
        }

        void OnBeginAttributes() override {
            ++AttributesDepth;
        }

        void OnEndAttributes() override {
            --AttributesDepth;
        }

    private:
        int AttributesDepth = 0;
    };

    using TJsonBuilder = TSkipAttributesProxy<TJsonBuilderImpl>;

    void ConvertJson2Yson(const NJson::TJsonValue& inputValue, IOutputStream* outputStream);
    void ConvertYson2Json(IInputStream* inputStream, NJson::TJsonValue* outputValue);
    void ConvertYson2Json(IInputStream* inputStream, IOutputStream* outputStream);
}
