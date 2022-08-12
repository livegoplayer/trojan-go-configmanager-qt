#ifndef RULELISTEDIT_H
#define RULELISTEDIT_H

#include "src/ui/additemdialog.h"
#include "src/config/configmanager.h"

#include <QDialog>

namespace Ui {
class RuleListEdit;
}

class RuleListEdit : public QDialog
{
    Q_OBJECT

public:
    explicit RuleListEdit(QWidget *parent = nullptr);
    ~RuleListEdit();

    int GetType();
    void SetType(int type);

    static int const BY_PASS_RULE_FORM = 0;
    static int const PROXY_RULE_FORM = 1;
    static int const BLOCK_RULE_FORM = 2;

    // 这里是默认的列表
    constexpr static const char category_ads[] = "geosite:category-ads";
    constexpr static const char category_ads_all[] = "geosite:category-ads-all";
    constexpr static const char tld_cn[] = "geosite:tld-cn";
    constexpr static const char notld_cn[] = "geosite:tld-!cn";
    constexpr static const char geolocation_cn[] = "geosite:geolocation-cn";
    constexpr static const char nogeolocation_cn[] = "geosite:geolocation-!cn";
    constexpr static const char cn[] = "geosite:cn";
    constexpr static const char apple[] = "geosite:apple";
    constexpr static const char google[] = "geosite:google";
    constexpr static const char microsoft[] = "geosite:microsoft";
    constexpr static const char facebook[] = "geosite:facebook";
    constexpr static const char twitter[] = "geosite:twitter";
    constexpr static const char telegram[] = "geosite:telegram";


    AddItemDialog *AddItemDialog;

    void InitByType(int type);
    void SaveRuleListByType();
    void AddItem(QString text);
    void DelSelctedItem();
    void ShowInWiget(QLayout *widget);
    void HideInWiget(QLayout *widget);
    void HideHelper();
    void HideDiyHelper();
    void ShowHelper();
    void ShowDiyHelper();
private:
    Ui::RuleListEdit *ui;

    int type;

public slots:
    void AddNewItem(QString text);
};

#endif // RULELISTEDIT_H
