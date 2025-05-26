#include <cassert>
#include <iostream>
#include "ArrayMutableSequence.hpp"
#include "ListMutableSequence.hpp"
#include "ArrayImmutableSequence.hpp"
#include "ListImmutableSequence.hpp"

void TestArrayMutableSequence()
{
    std::cout << "Тестирование ArrayMutableSequence..." << std::endl;
    int items[] = { 10, 20, 30, 40, 50 };
    ArrayMutableSequence<int> seq(items, 5);

    assert(seq.GetFirst() == 10);
    assert(seq.GetLast() == 50);
    assert(seq.Get(2) == 30);

    seq.AppendInPlace(60);
    assert(seq.GetLast() == 60);
    assert(seq.GetLength() == 6);

    seq.PrependInPlace(5);
    assert(seq.GetFirst() == 5);
    assert(seq.GetLength() == 7);

    seq.InsertAtInPlace(99, 3);
    assert(seq.Get(3) == 99);
    assert(seq.GetLength() == 8);

    seq[3] = 45;
    assert(seq[3] == 45);

    auto subSeq = seq.GetSubsequence(2, 5);
    assert(subSeq->GetLength() == 4);
    assert(subSeq->Get(0) == seq.Get(2));

    ArrayMutableSequence<int> otherSeq(items, 5);
    seq.ConcatInPlace(&otherSeq);
    assert(seq.GetLength() == 13);
    assert(seq.GetLast() == 50);

    auto mapped = seq.Map([](const int& x) { return x * 3; });
    assert(mapped->Get(0) == seq.Get(0) * 3);

    int product = seq.Reduce([](const int& acc, const int& x) { return acc * x; }, 1);
    assert(product > 0);

    auto filtered = seq.Where([](const int& x) { return x % 10 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i) {
        assert(filtered->Get(i) % 10 == 0);
    }

    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    int count = 0;
    for (auto& val : seq) {
        (void)val;
        count++;
    }
    assert(count == seq.GetLength());

    std::cout << "Тесты ArrayMutableSequence успешно пройдены!" << std::endl;
}

void TestListMutableSequence()
{
    std::cout << "Тестирование ListMutableSequence..." << std::endl;
    int items[] = { 15, 25, 35, 45, 55 };
    ListMutableSequence<int> seq(items, 5);

    assert(seq.GetFirst() == 15);
    assert(seq.GetLast() == 55);
    assert(seq.Get(2) == 35);

    seq.AppendInPlace(65);
    assert(seq.GetLast() == 65);
    assert(seq.GetLength() == 6);

    seq.PrependInPlace(5);
    assert(seq.GetFirst() == 5);
    assert(seq.GetLength() == 7);

    seq.InsertAtInPlace(88, 3);
    assert(seq.Get(3) == 88);
    assert(seq.GetLength() == 8);

    seq[3] = 40;
    assert(seq[3] == 40);

    auto subSeq = seq.GetSubsequence(2, 5);
    assert(subSeq->GetLength() == 4);
    assert(subSeq->Get(0) == seq.Get(2));

    ListMutableSequence<int> otherSeq(items, 5);
    seq.ConcatInPlace(&otherSeq);
    assert(seq.GetLength() == 13);
    assert(seq.GetLast() == 55);

    auto mapped = seq.Map([](const int& x) { return x + 10; });
    assert(mapped->Get(0) == seq.Get(0) + 10);

    int sum = seq.Reduce([](const int& acc, const int& x) { return acc + x; }, 0);
    assert(sum > 0);

    auto filtered = seq.Where([](const int& x) { return x > 30; });
    for (int i = 0; i < filtered->GetLength(); ++i) {
        assert(filtered->Get(i) > 30);
    }

    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    int count = 0;
    for (auto& val : seq) {
        (void)val;
        count++;
    }
    assert(count == seq.GetLength());

    std::cout << "Тесты ListMutableSequence успешно пройдены!" << std::endl;
}

void TestArrayImmutableSequence()
{
    std::cout << "Тестирование ArrayImmutableSequence..." << std::endl;
    int items[] = { 2, 4, 6, 8, 10 };
    ArrayImmutableSequence<int> seq(items, 5);

    assert(seq.GetFirst() == 2);
    assert(seq.GetLast() == 10);
    assert(seq.Get(2) == 6);

    auto appended = seq.Append(12);
    assert(appended->GetLast() == 12);
    assert(appended->GetLength() == 6);

    auto prepended = seq.Prepend(0);
    assert(prepended->GetFirst() == 0);
    assert(prepended->GetLength() == 6);

    auto inserted = seq.InsertAt(99, 3);
    assert(inserted->Get(3) == 99);
    assert(inserted->GetLength() == 6);

    auto subSeq = seq.GetSubsequence(1, 3);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(1));

    ArrayImmutableSequence<int> otherSeq(items, 5);
    auto concatenated = seq.Concat(&otherSeq);
    assert(concatenated->GetLength() == 10);
    assert(concatenated->GetLast() == 10);

    auto mapped = seq.Map([](const int& x) { return x / 2; });
    assert(mapped->Get(0) == seq.Get(0) / 2);

    int sum = seq.Reduce([](const int& acc, const int& x) { return acc + x; }, 0);
    assert(sum > 0);

    auto filtered = seq.Where([](const int& x) { return x % 4 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i) {
        assert(filtered->Get(i) % 4 == 0);
    }

    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    std::cout << "Тесты ArrayImmutableSequence успешно пройдены!" << std::endl;
}

void TestListImmutableSequence()
{
    std::cout << "Тестирование ListImmutableSequence..." << std::endl;
    int items[] = { 3, 6, 9, 12, 15 };
    ListImmutableSequence<int> seq(items, 5);

    assert(seq.GetFirst() == 3);
    assert(seq.GetLast() == 15);
    assert(seq.Get(2) == 9);

    auto appended = seq.Append(18);
    assert(appended->GetLast() == 18);
    assert(appended->GetLength() == 6);

    auto prepended = seq.Prepend(0);
    assert(prepended->GetFirst() == 0);
    assert(prepended->GetLength() == 6);

    auto inserted = seq.InsertAt(99, 3);
    assert(inserted->Get(3) == 99);
    assert(inserted->GetLength() == 6);

    auto subSeq = seq.GetSubsequence(1, 3);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(1));

    ListImmutableSequence<int> otherSeq(items, 5);
    auto concatenated = seq.Concat(&otherSeq);
    assert(concatenated->GetLength() == 10);
    assert(concatenated->GetLast() == 15);

    auto mapped = seq.Map([](const int& x) { return x - 1; });
    assert(mapped->Get(0) == seq.Get(0) - 1);

    int product = seq.Reduce([](const int& acc, const int& x) { return acc * x; }, 1);
    assert(product > 0);

    auto filtered = seq.Where([](const int& x) { return x % 3 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i) {
        assert(filtered->Get(i) % 3 == 0);
    }

    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    std::cout << "Тесты ListImmutableSequence успешно пройдены!" << std::endl;
}

int main()
{
    std::setlocale(LC_ALL, "Russian");

    TestArrayMutableSequence();
    TestListMutableSequence();
    TestArrayImmutableSequence();
    TestListImmutableSequence();

    std::cout << "Все тесты успешно пройдены!" << std::endl;
    return 0;
}