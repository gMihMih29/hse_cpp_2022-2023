# Правила оценивания

Общая формула оценки:

![encoding](https://latex.codecogs.com/svg.image?&space;0.3&space;\cdot&space;HW&space;&plus;&space;0.15&space;\cdot&space;HW_1&space;&plus;&space;0.15&space;\cdot&space;HW_2&space;&plus;&space;0.3&space;\cdot&space;E&space;&plus;&space;0.1&space;\cdot&space;S)

где
- ![encoding](https://latex.codecogs.com/svg.image?HW_{1,2}) - оценки за большие домашние задания
- ![encoding](https://latex.codecogs.com/svg.image?HW) - средняя оценка за каждое еженедельное задание
- ![encoding](https://latex.codecogs.com/svg.image?E) - оценка за экзамен
- ![encoding](https://latex.codecogs.com/svg.image?S) - оценка за работу на семинаре

Итоговая оценка округляется до ближайшего целого с помощью функции `std::round`.

## Домашние задания

Задача из домашнего задания считается сданной, если её решение проходит тесты и для неё закрыт Merge Request.

Начисление баллов за задачу:
- Задача, сданная до [дедлайна](https://cpp-hse.ru/), оценивается в `100%` возможных баллов.
- Между дедлайном и неделей после дедлайна баллы убывают линейно от 100% до 0%.
- За задачу, не сданную через неделю после дедлайна, баллы не начисляются.

 Оценки за недельные ДЗ нормируются до `10` и вычисляются по формуле:

  ![encoding](https://latex.codecogs.com/svg.image?\frac{Sum_{week}}{Max}&space;\times&space;10), где ![encoding](https://latex.codecogs.com/svg.image?Sum_{week}) - число набранных студентом баллов за недельное ДЗ, ![encoding](https://latex.codecogs.com/svg.image?Max) - максимально возможное число баллов за задачи недели
  
Итоговый балл за ДЗ ![encoding](https://latex.codecogs.com/svg.image?HW) является средней оценкой за недельные ДЗ и вычисляется по формуле:

  ![encoding](https://latex.codecogs.com/svg.image?\frac{Sum_{total}}{Weeks}), где ![encoding](https://latex.codecogs.com/svg.image?Sum_{total}) - сумма оценок за все недельные ДЗ, ![encoding](https://latex.codecogs.com/svg.image?Weeks) - количество выданных недельных ДЗ
