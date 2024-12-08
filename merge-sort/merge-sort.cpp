#include "merge-sort.hpp"
#include <memory>

List::List(std::initializer_list<int> list) {
    ListElement *tail = nullptr;
    for (auto number : list) {
        auto new_element = new ListElement{number, nullptr};
        if (tail == nullptr) {
            head = new_element;  // Инициализация head, если список пуст
        } else {
            tail->next = new_element;  // Добавляем элемент после tail
        }
        tail = new_element;  // Обновляем tail на новый последний элемент
    }
}

auto merge(List a, List b) noexcept -> List {
    List result;
    ListElement *tail = nullptr; // tail указывает на конец result

    while (a.head && b.head) {
        ListElement **min_element = nullptr;

        // Определяем, какой из элементов меньше
        if (a.head->value < b.head->value) {
            min_element = &a.head;
        } else {
            min_element = &b.head;
        }

        // Перемещаем минимальный элемент из списка `a` или `b` в `result`
        if (!result.head) {
            result.head = *min_element;
        } else {
            tail->next = *min_element;
        }

        // tail теперь указывает на только что добавленный элемент
        tail = *min_element;
        *min_element = (*min_element)->next;
    }

    // Переносим оставшийся список (если есть)
    tail->next = a.head ? a.head : b.head;

    return result;
}

auto mergesort(List &list) noexcept -> void {
    if (!list.head || !list.head->next) {
        return; // Базовый случай: пустой список или один элемент, сортировка не нужна
    }

    // Находим середину списка (быстрый и медленный указатели)
    ListElement *slow = list.head;
    ListElement *fast = list.head;
    ListElement *prev = nullptr;

    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // Разделяем список на две половины
    prev->next = nullptr;
    List second_half;
    second_half.head = slow;

    // Рекурсивно сортируем обе половины
    mergesort(list);
    mergesort(second_half);

    // Сливаем отсортированные половины
    list = merge(std::move(list), std::move(second_half));
}
