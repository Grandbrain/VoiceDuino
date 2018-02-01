#include <QStringList>
#include "string2number.h"

QString one_1       [] = { "ноль", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
QString one_2       [] = { "ноль", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
QString tens_1      [] = { "десять", "одинадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать" };
QString tens_2      [] = { "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто" };
QString hundreds    [] = { "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот" };
QString thousands   [] = { "тысяча", "тысяч", "тысячи" };

String2Number::String2Number()
{

}

int String2Number::string2number(const QString& data)
{
    int num_ones = 0;
    int num_tens = 0;
    int num_hundreds = 0;
    int num_thousand = 0;

    QStringList words = data.split(' ');
    int num_words = words.size();

    if (num_words == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (words[num_words - 1] == one_1[i])
            {
                num_ones = i;
                break;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            if (words[num_words - 1] == tens_1[i])
            {
                num_tens = 10 + i;
                break;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            if (words[num_words - 1] == tens_2[i])
            {
                if (i == 0) num_tens = 10 + 10;
                else num_tens = 10 + 10 * (i + 1);
                break;
            }
        }

        for (int i = 0; i < 9; i++)
        {
            if (words[num_words - 1] == hundreds[i])
            {
                if (i == 0) num_hundreds = 100;
                else num_hundreds = 100 * (i + 1);
                break;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (words[num_words - 1] == thousands[i])
            {
                if (i == 0) num_thousand = 1000;
                else num_thousand = 1000 * i;
                break;
            }
        }
    }
    else if (num_words == 2)
    {
        for (int n = 0; n < num_words; n++)
        {
            if (n == 0)
            {
                for (int i = 0; i < 10; i++)
                {
                    if (words[n] == one_2[i])
                    {
                        num_thousand = 1000 * i;
                        break;
                    }
                }

                for (int i = 0; i < 10; i++)
                {
                    if (words[n] == tens_2[i])
                    {
                        if (i == 0) num_tens = 10 + 10;
                        else num_tens = 10 + 10 * (i + 1);
                        break;
                    }
                }

                for (int i = 0; i < 9; i++)
                {
                    if (words[n] == hundreds[i])
                    {
                        if (i == 0) num_hundreds = 100;
                        else num_hundreds = 100 * (i + 1);
                        break;
                    }
                }

                for (int i = 0; i < 3; i++)
                {
                    if (words[n] == thousands[i])
                    {
                        if (i == 0) num_thousand = 1000;
                        break;
                    }
                }
            }
            else if (n == 1)
            {
                for (int i = 0; i < 10; i++)
                {
                    if (words[n] == one_1[i])
                    {
                        num_ones = i;
                        break;
                    }
                }

                for (int i = 0; i < 10; i++)
                {
                    if (words[n] == tens_1[i])
                    {
                        num_tens = 10 + i;
                        break;
                    }
                }

                for (int i = 0; i < 10; i++)
                {
                    if (words[n] == tens_2[i])
                    {
                        if (i == 0) num_tens = 10 + 10;
                        else num_tens = 10 + 10 * (i + 1);
                        break;
                    }
                }

                for (int i = 0; i < 9; i++)
                {
                    if (words[n] == hundreds[i])
                    {
                        if (i == 0) num_hundreds = 100;
                        else num_hundreds = 100 * (i + 1);
                        break;
                    }
                }

                for (int i = 0; i < 3; i++)
                {
                    if (words[n] == thousands[i])
                    {
                        if (i == 0) num_thousand = 1000;
                        break;
                    }
                }
            }
        }
    }

    return num_thousand+num_hundreds+num_tens+num_ones;
}
