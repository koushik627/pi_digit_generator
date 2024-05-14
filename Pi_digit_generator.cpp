// Number Theory:
// Assignment1,
// By - Rakshit Bang, NSP Kaushikh
// Roll - IMT2020105, IMT2020096
// Date - 05/04/2021

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
// Definition of Real Number
//////////////////////////////////////////////////////////////////////////////////////////////

struct Number
{
    vector<int> num;
    int precision;
};
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// General Functions used in Arithmetic Functions
//////////////////////////////////////////////////////////////////////////////////////////////

int makeEqualLength(struct Number &num1, struct Number &num2)
{
    int len;
    int len1 = (num1.num).size();
    int len2 = (num2.num).size();

    if (len1 < len2)
    {
        for (int i = 0; i < len2 - len1; i++)
        {
            (num1.num).insert((num1.num).begin(), 0);
        }
    }
    else if (len1 > len2)
    {
        for (int i = 0; i < len1 - len2; i++)
        {
            (num2.num).insert((num2.num).begin(), 0);
        }
    }
    if ((num1.num).size() == (num2.num).size())
    {
        len = (num1.num).size();
    }
    else
    {
        cout << "ERROR: Cannot make it of Equal Length \n";
    }
    return len;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void paddingToPrecision(struct Number &num1, struct Number &num2)
{
    if (num1.precision < num2.precision)
    {
        for (int i = 0; i < num2.precision - num1.precision; i++)
        {
            (num1.num).push_back(0);
        }
        num1.precision = num2.precision;
    }
    else if (num1.precision > num2.precision)
    {
        for (int i = 0; i < num1.precision - num2.precision; i++)
        {
            (num2.num).push_back(0);
        }
        num2.precision = num1.precision;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
bool isFirstSmaller(struct Number &num1, struct Number &num2)
{
    int len1 = (num1.num).size();
    int len2 = (num2.num).size();

    if (len1 < len2)
        return true;
    else if (len2 < len1)
        return false;
    else
    {
        for (int i = 0; i < len1; i++)
        {
            if (num1.num[i] < num2.num[i])
                return true;
            else if (num1.num[i] > num2.num[i])
                return false;
        }
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
struct Number MakeShifting(struct Number tobeShifted, int shiftCount)
{
    struct Number afterShift;
    for (int i = 0; i < (tobeShifted.num).size(); i++)
    {
        (afterShift.num).push_back(tobeShifted.num[i]);
    }
    for (int i = 0; i < shiftCount; i++)
    {
        (afterShift.num).push_back(0);
    }
    afterShift.precision = tobeShifted.precision;
    return afterShift;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void removePaddingZeros(struct Number &dividend, struct Number &divisor)
{
    while (dividend.num[0] == 0)
    {
        dividend.num.erase(dividend.num.begin());
    }
    while (divisor.num[0] == 0)
    {
        divisor.num.erase(divisor.num.begin());
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
void truncate(struct Number &x)
{
    while (x.num.at(0) == 0 && x.num.size() > 1)
    {
        x.num.erase(x.num.begin());
    }
    return;
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool isSame(struct Number &prev_root_X, struct Number &root_X, int p, int B)
{
    if (prev_root_X.precision == p && root_X.precision == p)
    {
        if (prev_root_X.num.size() == root_X.num.size())
        {
            for (int i = prev_root_X.num.size() - 1; i >= 0; i--)
            {
                if (prev_root_X.num[i] != root_X.num[i])
                    return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////

void padding(struct Number &x, int p)
{
    for (int i = 0; i < p; i++)
    {
        x.num.push_back(0);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Addition for Large Real Numbers
//////////////////////////////////////////////////////////////////////////////////////////////

struct Number largeIntegerAddition(int B, struct Number num1, struct Number num2)
{
    paddingToPrecision(num1, num2);

    int len = makeEqualLength(num1, num2);

    struct Number result;
    result.precision = max(num1.precision, num2.precision);

    int carry = 0;
    vector<int> temp;

    for (int i = len - 1; i >= 0; i--)
    {
        int sum = ((num1.num[i]) + (num2.num[i]) + carry);
        temp.push_back(sum % B);
        carry = sum / B;
    }
    if (carry > 0)
    {
        temp.push_back(carry);
        reverse(temp.begin(), temp.end());
        for (int i = 0; i < len + 1; i++)
        {
            (result.num).push_back(temp[i]);
        }
    }
    else
    {
        reverse(temp.begin(), temp.end());
        for (int i = 0; i < len; i++)
        {
            (result.num).push_back(temp[i]);
        }
    }
    return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Subtraction for Large Real Numbers
//////////////////////////////////////////////////////////////////////////////////////////////

struct Number largeIntegerSubtraction(int B, struct Number num1, struct Number num2)
{
    paddingToPrecision(num1, num2);

    int len = makeEqualLength(num1, num2);

    struct Number result;
    result.precision = max(num1.precision, num2.precision);

    int carry = 0;
    vector<int> temp;

    if (isFirstSmaller(num1, num2))
    {
        for (int i = len - 1; i >= 0; i--)
        {
            int diff = ((num2.num[i]) - (num1.num[i]) - carry);
            if (diff < 0)
            {
                diff += B;
                carry = 1;
            }
            else
                carry = 0;

            temp.push_back(diff);
        }
        temp[len - 1] = temp[len - 1] * -1;
    }
    else
    {
        for (int i = len - 1; i >= 0; i--)
        {
            int diff = ((num1.num[i]) - (num2.num[i]) - carry);
            if (diff < 0)
            {
                diff += B;
                carry = 1;
            }
            else
                carry = 0;

            temp.push_back(diff);
        }
    }
    reverse(temp.begin(), temp.end());
    for (int i = 0; i < len; i++)
    {
        (result.num).push_back(temp[i]);
    }
    return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Multiplication for Large Real Numbers
// By Using KaratSuba's Algorithm
//////////////////////////////////////////////////////////////////////////////////////////////

struct Number largeIntegerMultiplication(int B, struct Number num1, struct Number num2)
{
    int len = makeEqualLength(num1, num2);

    struct Number singleBitMultiplication;

    // Base Case
    if (len == 1)
    {
        singleBitMultiplication.precision = num1.precision + num2.precision;
        int x = (num1.num[0] * num2.num[0]) / B;
        int y = (num1.num[0] * num2.num[0]) % B;

        (singleBitMultiplication.num).push_back(x);
        (singleBitMultiplication.num).push_back(y);
        return singleBitMultiplication;
    }

    int lh = len / 2;
    int rh = (len - lh);

    struct Number num1L;
    num1L.precision = num1.precision;

    struct Number num1R;
    num1R.precision = num1.precision;

    struct Number num2L;
    num2L.precision = num2.precision;

    struct Number num2R;
    num2R.precision = num2.precision;

    for (int i = 0; i < lh; i++)
    {
        (num1L.num).push_back(num1.num[i]);
        (num2L.num).push_back(num2.num[i]);
    }
    for (int i = lh; i < len; i++)
    {
        (num1R.num).push_back(num1.num[i]);
        (num2R.num).push_back(num2.num[i]);
    }

    struct Number P1 = largeIntegerMultiplication(B, num1L, num2L);

    struct Number P2 = largeIntegerMultiplication(B, num1R, num2R);

    struct Number P3 = largeIntegerMultiplication(B, largeIntegerAddition(B, num1L, num1R),
                                                  largeIntegerAddition(B, num2L, num2R));

    struct Number P4 = largeIntegerSubtraction(B, largeIntegerSubtraction(B, P3, P1), P2);

    struct Number P5 = MakeShifting(P1, 2 * rh);

    struct Number P6 = MakeShifting(P4, rh);

    struct Number P7 = largeIntegerAddition(B, P5, P2);

    struct Number P8;
    if (P6.num[0] < 0)
    {
        P6.num[0] = P6.num[0] * -1;
        P8 = largeIntegerSubtraction(B, P7, P6);
    }
    else
        P8 = largeIntegerAddition(B, P7, P6);

    return P8;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Division for Large Real Numbers
//////////////////////////////////////////////////////////////////////////////////////////////

void largeIntegerDivision(int B, struct Number &num1, struct Number &num2, struct Number &quotient, struct Number &remainder)
{
    bool flag = false;
    int k = num1.num.size();
    int l = num2.num.size();
    int tmp, carry, count = 0;

    if (k < l)
    {
        quotient.num.push_back(0);
        for (int i = 0; i < k; i++)
        {
            remainder.num.push_back(num1.num.at(i));
        }
        return;
    }
    else if (l < k)
    {
        flag = true;
    }
    else
    {
        for (int i = 0; i < k; i++)
        {
            if (num1.num[i] > num2.num[i])
            {
                flag = true;
                break;
            }
            else if (num2.num[i] > num1.num[i])
            {
                quotient.num.push_back(0);
                for (int i = 0; i < k; i++)
                {
                    remainder.num.push_back(num1.num.at(i));
                }
                return;
            }
        }
        if (!flag)
        {
            quotient.num.push_back(1);
            remainder.num.push_back(0);
            return;
        }
    }

    k = num1.num.size();
    l = num2.num.size();

    reverse(num1.num.begin(), num1.num.end());
    reverse(num2.num.begin(), num2.num.end());

    for (int i = 0; i <= k - 1; i++)
    {
        remainder.num.push_back(num1.num.at(i));
    }
    remainder.num.push_back(0);

    for (int i = 0; i <= k - l; i++)
    {
        quotient.num.push_back(0);
    }

    for (int i = k - l; i >= 0; i--)
    {
        quotient.num.at(i) = floor((remainder.num.at(i + l) * B + remainder.num.at(i + l - 1)) / num2.num[l - 1]);
        if (quotient.num.at(i) >= B)
        {
            quotient.num.at(i) = B - 1;
        }

        carry = 0;
        count = 0;

        for (int j = 0; j <= l - 1; j++)
        {
            tmp = remainder.num.at(i + j) - quotient.num.at(i) * num2.num[j] + carry;
            carry = tmp / B;
            remainder.num.at(i + j) = tmp % B;
            if (remainder.num.at(i + j) < 0)
            {
                remainder.num.at(i + j) += B;
                carry--;
            }
        }
        remainder.num.at(i + l) = remainder.num.at(i + l) + carry;

        while (remainder.num.at(i + l) < 0)
        {
            carry = 0;
            for (int j = 0; j <= l - 1; j++)
            {
                tmp = remainder.num.at(i + j) + num2.num[j] + carry;
                carry = tmp / B;
                remainder.num.at(i + j) = tmp % B;
                if (remainder.num.at(i + j) < 0)
                {
                    remainder.num.at(i + j) += B;
                    carry--;
                }
            }
            remainder.num.at(i + l) = remainder.num.at(i + l) + carry;
            quotient.num.at(i) = quotient.num.at(i) - 1;
        }
    }

    reverse(quotient.num.begin(), quotient.num.end());
    reverse(remainder.num.begin(), remainder.num.end());

    for (int i = 0; i < quotient.num.size(); i++)
    {
        if (quotient.num.at(i) != 0)
        {
            truncate(quotient);
        }
    }
    return;
}

void largeRealDivision(int B, struct Number &num1,
                       struct Number &num2, struct Number &quotient,
                       struct Number &remainder, int p)
{
    paddingToPrecision(num1, num2);
    padding(num1, p);
    largeIntegerDivision(B, num1, num2, quotient, remainder);
    quotient.precision = p;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Square Root Calculator
//////////////////////////////////////////////////////////////////////////////////////////////

struct Number findRoot(struct Number &X, int m, int p)
{
    struct Number root_X;
    struct Number restore_X;
    struct Number prev_root_X;
    struct Number updated_root_X;

    struct Number temp_q;
    struct Number temp_r1;
    struct Number temp_add;
    struct Number temp_r2;

    struct Number two;
    two.num = {2};
    two.precision = 0;
    struct Number restore_two;

    root_X = X;
    restore_X = X;
    restore_two = two;

    int B = 10;

    while (true)
    {
        temp_q.num.clear();
        temp_r1.num.clear();
        temp_r2.num.clear();
        temp_add.num.clear();
        updated_root_X.num.clear();

        X = restore_X;
        two = restore_two;

        largeRealDivision(B, X, root_X, temp_q, temp_r1, p);

        reverse(root_X.num.begin(), root_X.num.end());

        temp_add = largeIntegerAddition(B, root_X, temp_q);

        largeRealDivision(B, temp_add, two, updated_root_X, temp_r2, p);

        if (!isSame(prev_root_X, updated_root_X, p, B))
        {
            prev_root_X = updated_root_X;
        }
        else
        {
            break;
        }
        root_X = updated_root_X;
    }

    return root_X;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Pi Digits Calculator
//////////////////////////////////////////////////////////////////////////////////////////////

struct Number PiCalc(int m, int p)
{
    p = p + 4;

    struct Number a_n;
    struct Number b_n;
    struct Number p_n;

    struct Number zero;
    zero.num = {0};
    zero.precision = p;

    struct Number one;
    one.num = {1};
    one.precision = 0;

    struct Number two;
    two.num = {2};
    two.precision = 0;

    struct Number tempOne = one;
    struct Number tempTwo = two;

    int B = 10;

    a_n = findRoot(two, B, p);

    b_n.num = {0};
    b_n.precision = p;

    two = tempTwo;
    p_n = largeIntegerAddition(B, two, a_n);

    struct Number a = a_n;
    struct Number b = b_n;
    struct Number Pi = p_n;
    struct Number a_back = a;
    struct Number b_back = b;
    struct Number root_ab;
    struct Number root_a;
    struct Number div_a;
    struct Number sum_a;

    struct Number prev_root_X;
    int i = 0;
    while (true)
    {
        prev_root_X = Pi;
        a_back = a;
        b_back = b;
        struct Number temp_r2;
        struct Number temp_r1;
        one = tempOne;
        root_a = findRoot(a, B, p);

        root_ab = root_a;

        largeRealDivision(B, one, root_a, div_a, temp_r1, p);

        root_a = root_ab;

        sum_a = largeIntegerAddition(B, root_a, div_a);

        struct Number tmp;
        two = tempTwo;
        largeRealDivision(B, sum_a, two, tmp, temp_r2, p);

        one = tempOne;
        struct Number sum_1b = largeIntegerAddition(B, one, b);

        a = a_back;

        struct Number sum_ab = largeIntegerAddition(B, a, b);

        root_a = root_ab;
        struct Number b_temp = largeIntegerMultiplication(B, root_a, sum_1b);

        struct Number b_final;
        struct Number rrr;
        largeRealDivision(B, b_temp, sum_ab, b_final, rrr, p);

        b = b_final;
        a = tmp;
        a_back = a;
        b_back = b;
        one = tempOne;

        struct Number x1 = largeIntegerAddition(B, one, a);

        a = a_back;

        struct Number x2 = largeIntegerMultiplication(B, Pi, x1);

        struct Number x3 = largeIntegerMultiplication(B, x2, b);

        one = tempOne;
        b = b_back;

        struct Number x4 = largeIntegerAddition(B, one, b);

        struct Number ror;
        struct Number x5;
        largeRealDivision(B, x3, x4, x5, ror, p);

        if (!isSame(prev_root_X, x5, p, B))
        {
            prev_root_X = x5;
        }
        else
        {
            break;
        }
        a = a_back;
        b = b_back;
        Pi = x5;

        i++;
    }
    for (int i = 0; i < 4; i++)
    {
        Pi.num.pop_back();
    }
    Pi.precision -= 4;
    return Pi;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Number Theory:
// Assignment1,
// By - Rakshit Bang, NSP Kaushikh
// Roll - IMT2020105, IMT2020096
// Date - 05/04/2021
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int root_or_pi;
    int precision;
    int m;

    cin >> root_or_pi >> precision >> m;

    if (root_or_pi == 1)
    {
        struct Number result = PiCalc(m, precision);
        cout << result.num[0] << ".";
        for (int i = 1; i < (result.num).size(); i++)
        {
            cout << result.num[i];
        }
        cout << endl;
    }
    else if (root_or_pi == 2)
    {
        struct Number two;
        two.num = {2};
        two.precision = 0;

        struct Number result = findRoot(two, m, precision);
        cout << result.num[0] << ".";
        for (int i = 0; i < (result.num).size(); i++)
        {
            cout << result.num[i];
        }
        cout << endl;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
