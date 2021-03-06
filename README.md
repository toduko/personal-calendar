# Личен календар

Проект 1 за курса по ООП на специалност Компютърни науки през летен семестър 2021-2022 учебна година.

## Условие на проекта

Да се напише програма, реализираща информационна система, която поддържа личен
календар, като го записва в текстов или двоичен файл по ваш избор.

Работата с програмата се осъществява в диалогов режим, като се поддържат следните
операции:

| Операция                 | Описание                                                                                                                                                                                                                                                                                                                       |
| ------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Запазване на час         | Запазва час за среща с дадено име, коментар, на дадена дата с даден начален и краен час.                                                                                                                                                                                                                                       |
| Отменяне на час          | Отменя час за среща по въведени данни за нея.                                                                                                                                                                                                                                                                                  |
| Дневна програма          | Извежда хронологичен списък с всички ангажименти за даден ден.                                                                                                                                                                                                                                                                 |
| Промяна на среща         | Променя датата, началния, крайния час, името на срещата или коментара към него. При промяна на дата и час се прави проверка дали са коректни и свободни.                                                                                                                                                                       |
| Търсене на среща         | Търсене на среща: извеждат се данните за всички срещи, в чието име или бележка се съдържа въведен низ.                                                                                                                                                                                                                         |
| Натовареност             | Извеждане на статистика за натовареност: по дадени начална и крайна дата се извежда списък с дните от седмицата, подредени по критерия “брой заети часове”. Информацията да се запише в текстов файл с име stats-YYYY-MM-DD.txt, където YYYY-MM-DD е началната дата от периода.                                                |
| Намиране на свободен час | Намиране на свободно място за среща: по дадена седмица и желана продължителност на срещата търси дата, на която е възможно да се запази такава среща, като търси само в предварително зададен интервал от часове (например от 8 до 17 часа). Начинът на указване на седмицата, в която се търси дата за среща, е по ваш избор. |

**Забележка:**

- Всички дати да се проверяват за коректност

## Решения на срещнати проблеми

- **Валидация на данни при създаването им**

За този проблем има няколко възможни решения. Едното е в конструктора да се хвърля изключение при грешно въведени данни, но това е лоша практика. Това може да се оправи със private конструктори и статични методи, които при невалидни данни хвърлят изключения, а при валидни данни те викат конструкторите. Пример:

```c++
class T {
private:
  T(const D& data) { /* do something with valid data */}
public:
  static T create(const D& data)
  {
    if (!isValid(data))
    {
      throw "Invalid data";
    }

    return T(data);
  }
};
```

- **Данни с динамична размерност**

Тук има две често срещани решения. Едното е клас `String`, който реализира динамичен по размер низ, другото е клас `Vector`, който реализира динамичен масив от произволен тип данни.

- **Копирането е бавна операция**

Най-често срещаното решение на този проблем е използването на указатели. Тяхната смяна е бърза. Този проблем се решава от класът `Optional`, който обвива данните в указател от техният тип.

- **Създаването на масиви иска конструктори по подразбиране**

Решението ми на този проблем също се крие във класът `Optional`. Той работи с указатели, но всеки тип указател си има конструктор по подразбиране.

## Възможни оптимизации

- **Нов клас `Interval`**

В момента в класът `Meeting` има логика за начална и крайна дата, която не трябва да е там. С цял по-добра абстракция може да се направи шаблонен клас `Interval`, който да проверява за сечение на интервали, подинтервали и подобни функционалности.

- **Рефакториране на класът `MeetingManager`**

Проблемът в момента, е че в проектът няма да може лесно да се интегрира клас, подобен на този. Начин този проблем да се оправи е като се направи един родителски клас `Manager`, със общи функции като търсене, премахване и промяна по няквакви критерии, който `MeetingManager` да наследява.

- **Пренаписване на класът `CLI`**

В момента класът `CLI` е тясно обвързан с класът `MeetingManager`. Възможно решение е класът при създаване да приема списък със наредени двойки **<Команда, Събитие>** и при дадена въведена команда, да я търси в този списък и да изпълни неговото събитие, ако я намери.

## Необходими програми

Проектът използва [GCC](https://gcc.gnu.org/) за компилация и [GNU Make](https://www.gnu.org/software/make/) за по-лесно произвеждане на изпълними файлове.

### Инсталация на Windows

[GCC изпълними файлове](https://gcc.gnu.org/install/binaries.html)

[Make програмен код](https://ftp.gnu.org/gnu/make/)

### Инсталация на Linux

GCC и Make могат да се инсталират от пакетният мениджър на конкретната дистрибуция.

Arch/Manjaro (pacman):

```bash
$ sudo pacman -S gcc make
```

Ubuntu/Debian (apt):

```bash
$ sudo apt install gcc make
```

Разбира се кодът може да се компилира ръчно с компилатор по избор.

## Използвани библиотеки

[Acutest](https://github.com/mity/acutest) за тестване на програмния код
