#include "yaoji.h"
#include"connectsql.h"
yaoji::yaoji(QObject *parent) :
    QObject(parent),m_YaojiList()
{
}

QList<int> yaoji::getYaojiList(void) const
{
    return m_YaojiList;
}

void yaoji::setYaojiList(const QList<int> YaojiList)
{
    m_YaojiList=YaojiList;
    emit YaojiListChanged();
}

void yaoji::updateYaojiList()
{
        sqlconnect("YaoJiDBF");//connect to sql

        QSqlQuery qry;
        QList<int> current_YaojiList;

        current_YaojiList<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0;//init, think of another way
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='碳酸钠' AND 加药点='碳酸钠搅拌桶' order by id desc ");//select last one
        qry.first();
        current_YaojiList[0]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='碳酸钠' AND 加药点='碳酸球磨池' order by id desc");
        qry.first();
        current_YaojiList[1]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='硫酸铜' AND 加药点='硫酸铜搅拌桶' order by id desc");
        qry.first();
        current_YaojiList[2]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='黄药' AND 加药点='黄药搅拌桶' order by id desc");
        qry.first();
        current_YaojiList[3]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='2#油' AND 加药点='2#油搅拌桶' order by id desc");
        qry.first();
        current_YaojiList[4]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='硫化钠' AND 加药点='硫化钠' order by id desc");
        qry.first();
        current_YaojiList[5]=qry.value(6).toInt();

        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='黑药' AND 加药点='黑药' order by id desc");
        qry.first();
        current_YaojiList[6]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='硫酸铜' AND 加药点='硫酸铜锑粗选' order by id desc");
        qry.first();
        current_YaojiList[7]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='硝酸铅' AND 加药点='硝酸铅锑粗选' order by id desc");
        qry.first();
        current_YaojiList[8]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='黄药' AND 加药点='黄药锑粗选' order by id desc");
        qry.first();
        current_YaojiList[9]=qry.value(6).toInt();
        qry.exec("SELECT Top 1 * FROM [YaoJiDBF].[dbo].[调节表] WHERE 药剂种类='2#油' AND 加药点='2#油锑粗选' order by id desc");
        qry.first();
        current_YaojiList[10]=qry.value(6).toInt();

        setYaojiList(current_YaojiList);
}
