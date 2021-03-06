# NarrativeFramework

Библиотека для представления нарративов (Stories) с возможностью кастомизации.

## Установка

| NarrativeFramework version | Build version | iOS version |
|----------------------------|---------------|-------------|
| 2.4.5                      | 376           | >= 9.0      |

Версию библиотеки можно получить из параметра `frameworkInfo`

### Ручная установка

Установка осуществляется путём подключения к проекту `NarrativesFramework.framework` библиотеки.

### Установка с CocoaPods

CocoaPods - это менеджер зависимостей для Objective-C, который автоматизирует и упрощает процесс использования сторонних библиотек в ваших проектах. Чтобы установить с CocoaPods, следуйте разделу «Get Started» на [CocoaPods](https://cocoapods.org/).
#### Podfile

```ruby
use_frameworks!
pod 'NarrativesFramework', :git => 'https://git.kiozk.ru/public-projects/narrativesframework.git'
```

#### Импорт библиотеки

##### Objective-C

```objective-c
#import <NarrativesFramework/NarrativesFramework.h>
```

##### Swift

```swift
import NarrativesFramework
```

### Отслеживание состояния приложения

Для корректного поведения повествований, необходимо в `AppDelegate`, рассылать уведомления `ResignActive`, `WillTerminate`, `EnterBackground`, `EnterForeground` и `BecomeActive`

##### Swift

```swift
func applicationWillResignActive(_ application: UIApplication) {
	NotificationCenter.default.post(name: NSNotification.Name(rawValue: "WillEnterBackground"), object: nil)
}

func applicationDidEnterBackground(_ application: UIApplication) {
	NotificationCenter.default.post(name: NSNotification.Name(rawValue: "EnterBackground"), object: nil)
}

func applicationWillEnterForeground(_ application: UIApplication) {
	NotificationCenter.default.post(name: NSNotification.Name(rawValue: "WillEnterForeground"), object: nil)
}

func applicationDidBecomeActive(_ application: UIApplication) {
	NotificationCenter.default.post(name: NSNotification.Name(rawValue: "EnterForeground"), object: nil)
}

func applicationWillTerminate(_ application: UIApplication) {
	NotificationCenter.default.post(name: NSNotification.Name(rawValue: "WillTerminate"), object: nil)
	sleep(3)
}
```

##### Obj-C

```obj-c
- (void)applicationWillResignActive:(UIApplication *)application {
	[[NSNotificationCenter defaultCenter] postNotificationName:@"WillEnterBackground" object:nil];
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
	[[NSNotificationCenter defaultCenter] postNotificationName:@"EnterBackground" object:nil];
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
	[[NSNotificationCenter defaultCenter] postNotificationName:@"WillEnterForeground" object:nil];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
	[[NSNotificationCenter defaultCenter] postNotificationName:@"EnterForeground" object:nil];
}

- (void)applicationWillTerminate:(UIApplication *)application {
[[NSNotificationCenter defaultCenter] postNotificationName:@"WillTerminate" object:nil];
	sleep(3)
}
```

### Удаление неиспользуемой архитектуры при компиляции

Выбирать проект, Выбрать Target → Project Name → Выбрать Build Phases → Нажать «+» → New Run Script Phase → Назовите скрипт «Remove Unused Architectures Script».

Скрипт необходимо добавить после "Embed Frameworks"

```bash
APP_PATH="${TARGET_BUILD_DIR}/${WRAPPER_NAME}"

find "$APP_PATH" -name '*.framework' -type d | while read -r FRAMEWORK
do
FRAMEWORK_EXECUTABLE_NAME=$(defaults read "$FRAMEWORK/Info.plist" CFBundleExecutable)
FRAMEWORK_EXECUTABLE_PATH="$FRAMEWORK/$FRAMEWORK_EXECUTABLE_NAME"
echo "Executable is $FRAMEWORK_EXECUTABLE_PATH"

EXTRACTED_ARCHS=()

for ARCH in $ARCHS
do
echo "Extracting $ARCH from $FRAMEWORK_EXECUTABLE_NAME"
lipo -extract "$ARCH" "$FRAMEWORK_EXECUTABLE_PATH" -o "$FRAMEWORK_EXECUTABLE_PATH-$ARCH"
EXTRACTED_ARCHS+=("$FRAMEWORK_EXECUTABLE_PATH-$ARCH")
done

echo "Merging extracted architectures: ${ARCHS}"
lipo -o "$FRAMEWORK_EXECUTABLE_PATH-merged" -create "${EXTRACTED_ARCHS[@]}"
rm "${EXTRACTED_ARCHS[@]}"

echo "Replacing original executable with thinned version"
rm "$FRAMEWORK_EXECUTABLE_PATH"
mv "$FRAMEWORK_EXECUTABLE_PATH-merged" "$FRAMEWORK_EXECUTABLE_PATH"

done
```
В Info.plist необходимо добавить ключ авторизации в сервисе, `authorize_key` – необходимо получить в CMS

```xml
<key>Narratives_Service_Key</key>
<string>authorize_key</string>
```

Так же в Info.plist можно установить сервер (Prod/Dev), к которому будет обращаться framework

```xml
<key>Narratives_sandbox</key>
<false/>
```

---
**Примечание**  

Так же данные параметры можно установить при инициализации, но обязательно до вызова метода `create()`. Параметры установленные при инициализации являются приоритетными и перекрывают значения установленные в Info.plist.

---

# NarrativesView
## Использование

Для корректного отображения статуса прочтения нарративов при инициализации `NarrativeView` необходимо передать ещё и уникальную строковую переменную привязанную к пользователю. Это может быть логин пользователя, id на сервере или в приложении. Основное условие, что бы ключ был уникальным для каждого пользователя.

Для таргетирования аудитории, необходимо добавить список тэгов (через запятую, без пробелов) в параметр `tags`.

Так же необходимо указать `targetController` с которого будут происходить переходы при выборе нарратива из списка.

Для запуска сессии и начала работы нарративов, необходимо вызвать метод `create()`

##### Swift

Инициализация:

```swift
override func viewDidLoad() {
	super.viewDidLoad()

	let narrativesView = NarrativesView(frame: .zero)
	narrativesView.serviceKey = "<ключ авторизации в сервисе> (String)"
	narrativesView.sandBox = "<сервер - Prod/Dev (Bool)>"
	narrativesView.uniqueKey = "<User unique key (String)>"
	narrativesView.tags = "<Список тагов через запятую>"
	narrativesView.targetController = self
	
	narrativesView.startNarrativeID = "<Narrative id (Int)>"

	view.addSubview(narrativesView)
	
	narrativesView.create()
}
```

##### Obj-C

Инициализация:

```obj-c
- (void)viewDidLoad {
	[super viewDidLoad];
    
	NFNarrativesView *narrativesView = [[NFNarrativesView alloc] initWithFrame:CGRectZero];
	narrativesView.serviceKey = @"<ключ авторизации в сервисе> (NSString)";
	narrativesView.sandBox = "<сервер - Prod/Dev (BOOL)";
	narrativesView.uniqueKey = @"<User unique key (NSString)>";
	narrativesView.tags = @"Список тагов через запятую";
	narrativesView.targetController = self;
	
	narrativesView.startNarrativeID = "<Narrative id (Int)>";
    
	[self.view addSubview:narrativesView];
	
	[narrativesView create];
}
```

### Методы

- Для обновления данных списка нарративов служит метод - `refreshNarratives`  
- Для программного отображения нарратива, без тапа на ячейку списка - `showNarrativeWithID:<int>`  
- Для отображения единичного нарратива, которого нет в списке - `showSingleNarrativeWithID:<int> fromTarget:<UIViewController>`  
- Для обновления данных нарратива представленого на экране служит метод - `refreshCurrentNarrative`  
- Для закрытия карточки нарратива из приложения служит метод - `closeNarrative`

##### Swift
```swift
narrativesView.showNarrative(withID: <Int>)
narrativesView.showSingleNarrative(withID: <Int>), fromTarget: <UIViewController>)
narrativesView.refreshNarratives()
narrativesView.refreshCurrentNarrative()
narrativesView.closeNarrative()
```

##### Obj-C

```obj-c
[narrativesView showNarrativeWithID:<int>];
[narrativesView showSingleNarrativeWithID:<int> fromTarget:<UIViewController>];
[narrativesView refreshNarratives];
[narrativesView refreshCurrentNarrative];
[narrativesView closeNarrative];
```

### Параметры и свойства
```swift
// Отслеживание наполнения списка нарративов
public var isContent: Bool
// Включение/отключение лайков в нутри нарратива
public var likePanel: Bool
// Включение/отключение избранного внутри нарратива и обработчика ячеки для избранного
public var favoritePanel: Bool
// Информация о версии библиотеки
public var frameworkInfo: String
```
### Кастомизация

#### Список повествований
```swift
// Заголовок списка. Если не задан, текстовое поле не отображается
public var title: String = ""
// Цвет заголовка ячейки нарратива
public var titleColor = UIColor.black
// Цвет Заголовка списка
public var titleColor: UIColor = UIColor.black
// Семейство шрифта заголовка
public var titleFontFamily: String = "AvenirNext-Regular"
// Размер шрифта заголовка
public var titleFontSize: CGFloat = 20.0
// Стиль отображения ячейки
public var cellStyle: CellStyle = .circle
// Цвет рамки ячейки
public var cellBorderColor: UIColor = UIColor.green
// Семейство шрифта названия ячейки
public var cellFontFamily: String = "AvenirNext-Medium"
// Размер шрифта названия ячейки
public var cellFontSize: CGFloat = 14.0
// Цвет названия ячейки
public var cellTitleColor: UIColor = UIColor.white
// Семейство шрифта источника ячейки
public var cellSourceFontFamily: String = "AvenirNext-Medium"
// Размер шрифта источника ячейки
public var cellSourceFontSize: CGFloat = 14.0
// Цвет источника ячейки
public var cellSourceTitleColor: UIColor = UIColor.darkGray
// Наличие контента в списке нарративов
public var isContent: Bool = false

// Цвет фона всего виджета
public var containerBackgroundColor: UIColor = UIColor.clear
// Цвет фона коллекции ячеек
public var listBackgroundColor: UIColor = UIColor.clear

// Расстояние между ячейками нарративов
public var cellSpacing: CGFloat = 0.0
// Отображения заголовка в ячейке нарратива
public var showingCellTitle: Bool = true
// Отображение источника под ячейкой нарратива
public var showingCellSource: Bool = true
```

#### Экран повествования
```swift
// Позиция кнопки "Закрыть"
public var closeButtonPosition: ClosePosition = .left
// Стиль перехода между наративами
public var scrollNarativeStyle: ScrollStyle = .flat
// Скрытие статусбара в наративе
public var showStatusBar: Bool = false
// Стиль показа экрана наративово (необходимо указать targetController)
// При использовании стиля .push, необходимо, что-бы targetController имел NavigationController,
// в противном случае будет присвоено значение .modal
public var presentationStyle: PresentationStyle = .crossDesolve
// Размер экрана нарратива на iPad
public var popupSize: CGSize = CGSize(width: 435, height: 675)
// Разрешить закрытие наратива по свайпу (только iPhone)
public var swipeToClose: Bool = true
// Разрешить закрытие наратива по свайпу на крайних нарративах (влево или в право)
public var overScrollToClose: Bool = true

// Цвет фона плэйсхолдеров на нарративе
public var placeholderBackgroundColor: UIColor = UIColor.black
// Цвет элемента в плейсхолдере на нарративе (кнопка "Обновить"/анимация)
public var placeholderElementColor: UIColor = UIColor.white

// Кастомизированный загрузчик повествования
public var placeholderView: (UIView & NarrativePlaceholderProtocol)? = nil

// Кастомизация иконок на панели лайков
public var likeImage: UIImage = nil
public var likeSelectedImage: UIImage = nil
public var dislikeImage: UIImage = nil
public var dislikeSelectedImage: UIImage = nil
// Кастомизация иконок на панели избранного
public var favoriteImage: UIImage = nil
public var favoriteSelectedImage: UIImage = nil
```

#### Собственная ячейка для списока повествований

Для использования собственной ячейки для списка повествований, необходимо у экзэмпляру класса `NarrativesView` указать `NarrativesViewCellDeleagate` и вызвать метод регистрации своей ячеки. 

Так же собственная ячейка должна реализовывать интерфейс(протокол) `NFNarrativeCellProtocol`  

При использовании собственной ячейки с включенным `likePanel = true` в списке нарративов, необходимо так же создать собственную ячейку для избранного которая будет реализовывать протокол `NFNarrativeFavoriteCellProtocol`


---
**Примечание**  

При использовании собственной ячейки, желательно переопределить ```func prepareForReuse()``` и обнулять цвета и данные наполнения полей и картинок.

##### Пример:
```swift
override func prepareForReuse() {
   imageView.alpha = 1.0
   imageView.image = nil
   imageView.backgroundColor = .white
   titleLabel.textColor = .black
   titleLabel.text = ""
}
```

---

##### Swift
```swift
narativesView.cellDelegate = self
narativesView.register(UINib(nibName: "CustomNarrativeCell", bundle: Bundle(for: type(of: self))), forCellWithReuseIdentifier: "CustomNarrativeCell")
```

##### Obj-C
```obj-c
narrativesView.cellDelegate = self;
[narrativesView registerNib:[UINib nibWithNibName:@"CustomNarrativeCell" bundle:[NSBundle mainBundle]] forCellWithReuseIdentifier:@"CustomNarrativeCell"];
```

#### NarrativesViewCellDeleagate
```obj-c
- (nonnull __kindof UICollectionViewCell<NFNarrativeCellProtocol> *)narrativesCollectionView:(nonnull UICollectionView *)collectionView cellForItemAtIndexPath:(nonnull NSIndexPath *)indexPath;
- (UIEdgeInsets)narrativesCollectionViewLayout:(nonnull UICollectionViewLayout *)collectionViewLayout insetForSectionAtIndex:(NSInteger)section
- (CGFloat)narrativesCollectionViewLayout:(nonnull UICollectionViewLayout *)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section
- (CGSize)narrativesCollectionViewLayout:(nonnull UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(nonnull NSIndexPath *)indexPath
```

#### NFNarrativeCellProtocol
```obj-c
- (void)setTitle:(NSString *)text;
- (void)setTitleColor:(UIColor *)color;
- (void)setSource:(NSString *)text;
- (void)setImageStringUrl:(NSString *)stringUrl;
- (void)setReaded:(BOOL)readed;
- (void)setHighlight:(BOOL)highlight;
- (void)setBackColor:(UIColor *)color;
```

#### NFNarrativeFavoriteCellProtocol
```obj-c
- (void)setFavoritesImages:(NSArray<NSString *> *)narrativesImages;
- (void)setHighlight:(BOOL)highlight;
```

## События

#### NFNarrativesViewDelegate
```obj-c
// Обновление контента списка нарративов
- (void)narrativeViewUpdated:(NFNarrativesView *)narrativeView;
// Получение ссылки из карточки нарратива (в основном по нажатию на кнопку)
- (void)narrativeView:(NFNarrativesView *)narrativeView getLinkWithTarget:(NSString *)target;
// Отслеживание закрытия ридера нарративов
- (void)narativeReaderDidClose;
// Отслеживание нажатия ячейки с избранными нарративами
- (void)favoriteCellDidSelect;
```

#### NotificationCenter
Для отслеживания поведения экранов внутри библиотеки. Используются в основном для аналитики.

*   `NarrativesViewSetup` - завершена настройка UIView повествований
*   `GetNarrativesComplete` - завершено получение списка повествований
*   `NarrativeReaded` - наратив прочитан - userInfo: ["id": Int]
*   `DidSelectNarrative` - выбор повествования в списке
*   `OpenNarrativeLink` - открытие ссылки из повествования - userInfo: ["linkType": String]
*   `NarrativeReaderOpen` - открыт повествованя
*   `NarrativeReaderClose` - закрытие повествованя
*   `NarrativeDidScroll` - повествование был перелистнут
*   `ArticleReaderOpen` - открыт статьи
*   `ArticleReaderClose` - закрытие статьи

##### NotificationCenter Ошибки
В уведомлениях об ошибке так же приходит `userInfo` в виде словаря `["errorMessage" : <Error_message_string>]`

*   `SessionFailure` - ошибка при работе с сессией
*   `NarrativeFailure` - ошибка при работе с нарративами
*   `ArticleFailure` - ошибка при работе со статьями
*   `CurrentNarrativeFailure` - ошибка при загрузке полной информации по нарративу
*   `NetworkFailure` - ошибка при работе сетью (нет интернета)

# PopupNarratives
## Использование

Для корректного отображения статуса прочтения нарративов при инициализации `PopupNarratives` необходимо передать ещё и уникальную строковую переменную привязанную к пользователю. Это может быть логин пользователя, id на сервере или в приложении. Основное условие, что бы ключ был уникальным для каждого пользователя.

Для таргетирования аудитории, необходимо добавить список тэгов (через запятую, без пробелов) в параметр `tags`.

Для запуска сессии и начала работы нарративов, необходимо вызвать метод `create()`

##### Swift

Импорт:

```swift
import NarrativesFramework
```

Инициализация:

```swift
override func viewDidLoad() {
	super.viewDidLoad()

	let popupNarratives = PopupNarratives()
	popupNarratives = "<User unique key (String)>"
	popupNarratives = "Список тагов через запятую"
	
	popupNarratives.create()
}
```

##### Obj-C

Импорт:

```obj-c
#import "LGAlertView.h"
```

Инициализация:

```obj-c
- (void)viewDidLoad {
	[super viewDidLoad];
    
	NFPopupNarratives * popupNarratives = [NFPopupNarratives new];
	popupNarratives.uniqueKey = @"<User unique key (NSString)>";
	popupNarratives.tags = @"Список тагов через запятую";
	
	[popupNarratives create];
}
```

### Методы

- Для программного отображения нарратива из контроллера - `showNarrativesFrom:<UIViewController>`  
- Для обновления данных нарратива представленого на экране служит метод - `refreshCurrentNarrative`  
- Для закрытия карточки нарратива из приложения служит метод - `closeNarrative`

##### Swift
```swift
popupNarratives.show(from: self)
popupNarratives.refreshCurrentNarrative()
popupNarratives.closeNarrative()
```

##### Obj-C

```obj-c
[popupNarratives showNarrativesFrom:self];
[popupNarratives refreshCurrentNarrative];
[popupNarratives closeNarrative];
```

##### Swift
```swift
print(popupNarratives.frameworkInfo)
```

##### Obj-C

```obj-c
NSLog(@"%@", popupNarratives.frameworkInfo);
```

### Параметры и свойства
```swift
// Отслеживание наполнения списка нарративов
public var isContent: Bool
// Включение/отключение лайков в нутри нарратива
public var likePanel: Bool
// Включение/отключение избранного внутри нарратива и обработчика ячеки для избранного
public var favoritePanel: Bool
// Информация о версии библиотеки
public var frameworkInfo: String
```

### Кастомизация

#### Экран повествования
```swift
// Позиция кнопки "Закрыть"
public var closeButtonPosition: ClosePosition = .left
// Стиль перехода между наративами
public var scrollNarativeStyle: ScrollStyle = .flat
// Скрытие статусбара в наративе
public var showStatusBar: Bool = false
// Стиль показа экрана наративово (необходимо указать targetController)
// При использовании стиля .push, необходимо, что-бы targetController имел NavigationController,
// в противном случае будет присвоено значение .modal
public var presentationStyle: PresentationStyle = .crossDesolve
// Размер экрана нарратива на iPad
public var popupSize: CGSize = CGSize(width: 435, height: 675)
// Разрешить закрытие наратива по свайпу (только iPhone)
public var swipeToClose: Bool = true

// Кастомизированный загрузчик повествования
public var placeholderView: (UIView & NarrativePlaceholderProtocol)? = nil

// Кастомизация иконок на панели лайков
public var likeImage: UIImage = nil
public var likeSelectedImage: UIImage = nil
public var dislikeImage: UIImage = nil
public var dislikeSelectedImage: UIImage = nil
// Кастомизация иконок на панели избранного
public var favoriteImage: UIImage = nil
public var favoriteSelectedImage: UIImage = nil
```

## События

#### NFPopupNarrativesDelegate
```obj-c
// Обновление контента списка нарративов
- (void)popupNarrativesUpdated:(NFPopupNarratives *)popupNarratives;
// Получение ссылки из карточки нарратива (в основном по нажатию на кнопку)
- (void)popupNarratives:(NFPopupNarratives *)popupNarratives getLinkWithTarget:(NSString *)target;
//Отслеживание закрытия ридера нарративов
- (void)popupNarativeReaderDidClose;
```

#### NotificationCenter
Для отслеживания поведения экранов внутри библиотеки. Используются в основном для аналитики.

*   `GetPopupNarrativesComplete` - завершено получение списка повествований
*   `PopupNarrativeReaded` - наратив прочитан - userInfo: ["id": Int]
*   `PopupNarrativeOpenLink` - открытие ссылки из повествования - userInfo: ["linkType": String]
*   `PopupNarrativeReaderOpen` - открытие повествованя
*   `PopupNarrativeReaderClose` - закрытие повествованя
*   `PopupNarrativeDidScroll` - повествование был перелистнут
*   `ArticleReaderOpen` - открытие статьи
*   `ArticleReaderClose` - закрытие статьи

##### NotificationCenter Ошибки
В уведомлениях об ошибке так же приходит `userInfo` в виде словаря `["errorMessage" : <Error_message_string>]`

*   `PopupSessionFailure` - ошибка при работе с сессией
*   `PopupNarrativeFailure` - ошибка при работе с нарративами
*   `ArticleFailure` - ошибка при работе со статьями
*   `CurrentPopupNarrativeFailure` - ошибка при загрузке полной информации по нарративу
*   `NetworkFailure` - ошибка при работе сетью (нет интернета)
    
# FavoriteNarrativesView
## Использование

`FavoriteNarrativesView` для отображения контента использует тот же параметр `uniqueKey`, что и `NarrativesView`, по этому при создании экрана избранных нарративов его задавать не нужно.

Для начала работы избранных нарративов, необходимо вызвать метод `create()`

##### Swift

Импорт:

```swift
import NarrativesFramework
```

Инициализация:

```swift
override func viewDidLoad() {
	super.viewDidLoad()

	let favoriteNarratives = FavoriteNarrativesView(frame: .zero)
	
	favoriteNarratives.create()
}
```

##### Obj-C

Импорт:

```obj-c
#import "LGAlertView.h"
```

Инициализация:

```obj-c
- (void)viewDidLoad {
	[super viewDidLoad];
    
	NFFavoriteNarrativesView * favoriteNarratives = [NFFavoriteNarrativesView alloc] initWithFrame:CGRectZero];
	
	[favoriteNarratives create];
}
```

### Методы

- Для обновления данных нарратива представленого на экране служит метод - `refreshCurrentNarrative`  
- Для закрытия карточки нарратива из приложения служит метод - `closeNarrative`

##### Swift
```swift
popupNarratives.refreshCurrentNarrative()
popupNarratives.closeNarrative()
```

##### Obj-C

```obj-c
[popupNarratives refreshCurrentNarrative];
[popupNarratives closeNarrative];
```

### Параметры и свойства
```swift
// Отслеживание наполнения списка нарративов
public var isContent: Bool
// Включение/отключение лайков в нутри нарратива
public var likePanel: Bool
// Включение/отключение избранного внутри нарратива и обработчика ячеки для избранного
public var favoritePanel: Bool
// Информация о версии библиотеки
public var frameworkInfo: String
```

### Кастомизация

#### Список повествований
```swift
// Стиль отображения ячейки
public var cellStyle: CellStyle = .circle
// Цвет рамки ячейки
public var cellBorderColor: UIColor = UIColor.green
// Семейство шрифта названия ячейки
public var cellFontFamily: String = "AvenirNext-Medium"
// Размер шрифта названия ячейки
public var cellFontSize: CGFloat = 14.0
// Цвет названия ячейки
public var cellTitleColor: UIColor = UIColor.white
// Семейство шрифта источника ячейки
public var cellSourceFontFamily: String = "AvenirNext-Medium"
// Размер шрифта источника ячейки
public var cellSourceFontSize: CGFloat = 14.0
// Цвет источника ячейки
public var cellSourceTitleColor: UIColor = UIColor.darkGray
// Наличие контента в списке нарративов
public var isContent: Bool = false

// Расстояние между ячейками нарративов
public var cellSpacing: CGFloat = 0.0
// Отображения заголовка в ячейке нарратива
public var showingCellTitle: Bool = true
// Отображение источника под ячейкой нарратива
public var showingCellSource: Bool = true
```

#### Экран повествования
```swift
// Позиция кнопки "Закрыть"
public var closeButtonPosition: ClosePosition = .left
// Стиль перехода между наративами
public var scrollNarativeStyle: ScrollStyle = .flat
// Скрытие статусбара в наративе
public var showStatusBar: Bool = false
// Стиль показа экрана наративово (необходимо указать targetController)
// При использовании стиля .push, необходимо, что-бы targetController имел NavigationController,
// в противном случае будет присвоено значение .modal
public var presentationStyle: PresentationStyle = .crossDesolve
// Размер экрана нарратива на iPad
public var popupSize: CGSize = CGSize(width: 435, height: 675)
// Разрешить закрытие наратива по свайпу (только iPhone и presentationStyle == (.modal || .crossDesolve))
public var swipeToClose: Bool = true
// Разрешить закрытие наратива по свайпу на крайних нарративах (влево или в право)
public var overScrollToClose: Bool = true

// Цвет фона плэйсхолдеров на нарративе
public var placeholderBackgroundColor: UIColor = UIColor.black
// Цвет элемента в плейсхолдере на нарративе (кнопка "Обновить"/анимация)
public var placeholderElementColor: UIColor = UIColor.white

// Кастомизированный загрузчик повествования
public var placeholderView: (UIView & NarrativePlaceholderProtocol)? = nil

// Кастомизация иконок на панели лайков
public var likeImage: UIImage = nil
public var likeSelectedImage: UIImage = nil
public var dislikeImage: UIImage = nil
public var dislikeSelectedImage: UIImage = nil
// Кастомизация иконок на панели избранного
public var favoriteImage: UIImage = nil
public var favoriteSelectedImage: UIImage = nil
```

## События

#### NFFavoriteNarrativesViewDelegate
```obj-c
// Отслеживание обновления нарративов внутри FavoriteNarrativesView
- (void)favoriteNarrativeViewUpdated:(NFFavoriteNarrativesView *)favoriteNarrativeView
// Обработка нажатия на кнопку внутри карточки нарратива
- (void)favoriteNarrativeView:(NFFavoriteNarrativesView *)favoriteNarrativeView getLinkWithTarget:(NSString *)target
// Отслеживание закрытия ридера нарративов
- (void)favoriteNarativeReaderDidClose
```

#### NotificationCenter
Для отслеживания поведения экранов внутри библиотеки. Используются в основном для аналитики.

*   `GetFavoriteNarrativesComplete` - завершено получение списка повествований
*   `FavoriteNarrativeReaded` - наратив прочитан - userInfo: ["id": Int]
*   `OpenFavoriteNarrativeLink` - открытие ссылки из повествования - userInfo: ["linkType": String]
*   `FavoriteNarrativeReaderOpen` - открытие повествованя
*   `FavoriteNarrativeReaderClose` - закрытие повествованя
*   `FavoriteNarrativeDidScroll` - повествование был перелистнут
*   `ArticleReaderOpen` - открытие статьи
*   `ArticleReaderClose` - закрытие статьи

##### NotificationCenter Ошибки
В уведомлениях об ошибке так же приходит `userInfo` в виде словаря `["errorMessage" : <Error_message_string>]`

*   `FavoriteNarrativeFailure` - ошибка при работе с нарративами
*   `ArticleFailure` - ошибка при работе со статьями
*   `CurrentFavoriteNarrativeFailure` - ошибка при загрузке полной информации по нарративу
*   `NetworkFailure` - ошибка при работе сетью (нет интернета)