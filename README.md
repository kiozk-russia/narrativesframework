# NarrativeFramework

Библиотека для представления нарративов (Stories) с возможностью кастомизации.

## Установка

| NarrativeFramework version | Build version | iOS version |
|----------------------------|---------------|-------------|
| 2.0.0                      | 200           | >= 9.0      |

Версию библиотеки можно получить из параметра `frameworkInfo`

### Ручная установка

Установка осуществляется путём подключения к проекту `NarrativesFramework.framework` библиотеки.

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

## Использование

Для корректного отображения статуса прочтения нарративов при инициализации `NarrativeView` необходимо передать ещё и уникальную строковую переменную привязанную к пользователю. Это может быть логин пользователя, id на сервере или в приложении. Основное условие, что бы ключ был уникальным для каждого пользователя.

Для таргетирования аудитории, необходимо добавить список тэгов (через запятую, без пробелов) в параметр `tags`.

Так же необходимо указать `targetController` с которого будут происходить переходы при выборе нарратива из списка.

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

	let narrativesView = NarrativesView(frame: .zero)
	narrativesView.uniqueKey = "<User unique key (String)>"
	narrativesView.tags = "Список тагов через запятую"
	narrativesView.targetController = self

	view.addSubview(narrativesView)
	
	narrativesView.create()
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
    
	NFNarrativesView *narrativesView = [[NFNarrativesView alloc] initWithFrame:CGRectZero];
	narrativesView.uniqueKey = @"<User unique key (NSString)>";
	narrativesView.tags = @"Список тагов через запятую";
	narrativesView.targetController = self;
    
	[self.view addSubview:narrativesView];
	
	[narrativesView create];
}
```

### Методы

- Для обновления данных списка нарративов служит метод - `refreshNarratives`  
- Для обновления данных нарратива представленого на экране служит метод - `refreshCurrentNarrative`  
- Для закрытия карточки нарратива из приложения служит метод - `closeNarrative`

##### Swift
```swift
narativesView.refreshNarratives()
narativesView.refreshCurrentNarrative()
narativesView.closeNarrative()
```

##### Obj-C

```obj-c
[narrativesView refreshNarratives];
[narrativesView refreshCurrentNarrative];
[narrativesView closeNarrative];
```

### Информация

Информацию о библиотеке можно получить из свойства `frameworkInfo`

##### Swift
```swift
print(narativesView.frameworkInfo)
```

##### Obj-C

```obj-c
NSLog(@"%@", narrativesView.frameworkInfo);
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

### Кастомизация

#### Список повествований
```swift
// Заголовок списка. Если не задан, текстовое поле не отображается
public var title: String = ""
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
```

#### Собственная ячейка для списока повествований

Для использования собственной ячейки для списка повествований, необходимо у экзэмпляру класса `NarrativesView` указать `NarrativesViewCellDeleagate` и вызвать метод регистрации своей ячеки. 

Так же собственная ячейка должна реализовывать интерфейс(протокол) `NFNarrativeCellProtocol`

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
- (void)setSource:(NSString *)text;
- (void)setImageStringUrl:(NSString *)stringUrl;
- (void)setReaded:(BOOL)readed;
- (void)setHighlight:(BOOL)highlight;
- (void)setBackgroundColor:(UIColor *)color;
```

## События

#### NFNarrativesViewDelegate
```obj-c
// Обновление контента списка нарративов
- (void)narrativeViewUpdated:(NFNarrativesView *)narrativeView;
// Получение ссылки из карточки нарратива (в основном по нажатию на кнопку)
- (void)narrativeView:(NFNarrativesView *)narrativeView getLinkWithTarget:(NSString *)target;
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
*   `NarativeFailure` - ошибка при работе с нарративами
*   `ArticleFailure` - ошибка при работе со статьями
*   `CurrentNarrativeFailure` - ошибка при загрузке полной информации по нарративу
*   `NetworkFailure` - ошибка при работе сетью (нет интернета)