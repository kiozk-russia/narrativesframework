//
//  NFNarrativesView.h
//  NarrativesFramework
//
//  Created by StPashik on 21/05/2019.
//  Copyright © 2019 kiozk. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Стиль отображение стандартной ячейки нарративов.
 При использовании собственной ячейки и NFNarrativesViewCellDeleagate - не используется.

 - NFNarrativeCellStyleCircle: круг
 - NFNarrativeCellStyleQuad: квадрат
 - NFNarrativeCellStyleRectangle: прямоугольник
 */
typedef NS_ENUM(NSUInteger, NFNarrativeCellStyle) {
    NFNarrativeCellStyleCircle     = 0,
    NFNarrativeCellStyleQuad       = 1,
    NFNarrativeCellStyleRectangle  = 2
} NS_SWIFT_NAME(CellStyle);

/**
 Позиция кнопки "Закрыть" (крестик) в карточке нарратива

 - NFNarrativeCloseButtonPositionLeft: слева от таймера
 - NFNarrativeCloseButtonPositionRight: справа от таймера
 */
typedef NS_ENUM(NSUInteger, NFNarrativeClosePosition) {
    NFNarrativeCloseButtonPositionLeft  = 0,
    NFNarrativeCloseButtonPositionRight = 1,
    NFNarrativeCloseButtonPositionBottomLeft = 2,
    NFNarrativeCloseButtonPositionBottomRight = 3
} NS_SWIFT_NAME(ClosePosition);

/**
 Стиль перелиствания нарративов в ридере

 - NFNarrativeScrollStyleFlat: простое слистывание
 - NFNarrativeScrollStyleCover: наплыв одной карточки на другую
 - NFNarrativeScrollStyleCube: 3D куб
 */
typedef NS_ENUM(NSUInteger, NFNarrativeScrollStyle) {
    NFNarrativeScrollStyleFlat  = 0,
    NFNarrativeScrollStyleCover = 1,
    NFNarrativeScrollStyleCube  = 2
} NS_SWIFT_NAME(ScrollStyle);

/**
 Тип представления ридера нарративов

 - NFNarrativePresentationStylePush: Push(Show) - только для iPhone и при наличии NavigationController
 - NFNarrativePresentationStyleCrossDesolve: предстваление через прозрачность
 - NFNarrativePresentationStyleModal: Модальное представление
 */
typedef NS_ENUM(NSUInteger, NFNarrativePresentationStyle) {
    NFNarrativePresentationStylePush         = 0,
    NFNarrativePresentationStyleCrossDesolve = 1,
    NFNarrativePresentationStyleModal        = 2
} NS_SWIFT_NAME(PresentationStyle);

/**
 Тип списка нарративов, используется для определения работы ридера
 */
typedef NS_ENUM(NSUInteger, NFNarrativeListType) {
    NFNarrativeListTypeList  = 0,
    NFNarrativeListTypePopup = 1,
    NFNarrativeListTypeSingle = 2,
    NFNarrativeListTypeFavorite = 3
} NS_SWIFT_NAME(NarrativeListType);

@class NFNarrativesView;

NS_SWIFT_NAME(NarrativeCellProtocol)
/**
 Протокол (интерфейс) собственной ячейки, который необходимо реализовать
 */
@protocol NFNarrativeCellProtocol <NSObject>
@required
/**
 Установка заголовка ячейки

 @param text заголовок ячейки
 */
- (void)setTitle:(NSString *)text;

/**
 Установка источника нарратива

 @param text источник нарратива
 */
- (void)setSource:(NSString *)text;

/**
 Установка картинки в ячеки по её URL в текстовом формате

 @param stringUrl URL картинки в текстовом формате
 */
- (void)setImageStringUrl:(NSString *)stringUrl;

/**
 Установка флага прочтения нарратива

 @param readed прочитан ли нарратив
 */
- (void)setReaded:(BOOL)readed;

/**
 Выделение ячейки при нажатии на неё

 @param highlight выделена ли ячейка
 */
- (void)setHighlight:(BOOL)highlight;

/**
 Установка цвета фона ячейки
 
 @param color цвет
 */
- (void)setBackColor:(UIColor *)color;

/**
 Установка цвета заголовка ячейки
 
 @param color цвет
 */
- (void)setTitleColor:(UIColor *)color;
@end

NS_SWIFT_NAME(NarrativeFavoriteCellProtocol)
/**
 Протокол (интерфейс) собственной ячейки для избранного, который необходимо реализовать
 */
@protocol NFNarrativeFavoriteCellProtocol <NSObject>
@required
/**
Установка картинок для ячейки избранного

@param narrativesImages список адресов картинок из избранного
*/
- (void)setFavoritesImages:(NSArray<NSString *> *)narrativesImages;
/**
 Выделение ячейки при нажатии на неё

 @param highlight выделена ли ячейка
 */
- (void)setHighlight:(BOOL)highlight;

@end

NS_SWIFT_NAME(NarrativePlaceholderProtocol)
/**
 Протокол (интерфейс) собственного загрузчика в нарративе, который необходимо реализовать
 */
@protocol NFNarrativePlaceholderProtocol <NSObject>
@required
/**
 Установка прогресса загрузки

 @param progress заголовок ячейки
 */
- (void)setProgress:(double)progress;

@optional
/**
 Является ли анимация в плейсхолдере зацикленной
 */
- (BOOL)isInfinity;
/**
Проигрывается ли анимация
*/
- (BOOL)isAnimate;
/**
 Если Placeholder зацикленный, запус анимации
 */
- (void)start;
/**
 Если Placeholder зацикленный, остановка анимации
 */
- (void)stop;
@end

NS_SWIFT_NAME(NarrativesViewDelegate)
/**
 Протокол делегата для отслеживания действий NarrativesView
 */
@protocol NFNarrativesViewDelegate <NSObject>
@optional
/**
 Отслеживание обновления нарративов внутри NarrativesView

 @param narrativeView NarrativesView
 */
- (void)narrativeViewUpdated:(NFNarrativesView *)narrativeView;

/**
 Обработка нажатия на кнопку внутри карточки нарратива

 @param narrativeView NarrativesView
 @param target сстылка переданная от кнопки внутри карточки
 */
- (void)narrativeView:(NFNarrativesView *)narrativeView getLinkWithTarget:(NSString *)target;

/**
 Отслеживание закрытия ридера нарративов
 */
- (void)narativeReaderDidClose;

/**
Отслеживание нажатия ячейки с избранными нарративами
*/
- (void)favoriteCellDidSelect;
@end

NS_SWIFT_NAME(NarrativesViewCellDeleagate)
/**
 Протокол делегата для установки параметров при использовании собственной ячейки
 */
@protocol NFNarrativesViewCellDeleagate <NSObject>
- (__kindof UICollectionViewCell <NFNarrativeCellProtocol> *)narrativesCollectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
NS_SWIFT_NAME(narrativesCollectionView(_:cellForItemAt:));
- (__kindof UICollectionViewCell <NFNarrativeFavoriteCellProtocol> *)narrativesCollectionView:(UICollectionView *)collectionView favoriteCellForItemAtIndexPath:(NSIndexPath *)indexPath
NS_SWIFT_NAME(narrativesCollectionView(_:favoriteCellForItemAt:));
- (CGSize)narrativesCollectionViewLayout:(UICollectionViewLayout*)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath
NS_SWIFT_NAME(narrativesCollectionViewLayout(_:sizeForItemAt:));
- (UIEdgeInsets)narrativesCollectionViewLayout:(UICollectionViewLayout*)collectionViewLayout insetForSectionAtIndex:(NSInteger)section
NS_SWIFT_NAME(narrativesCollectionViewLayout(_:insetForSectionAt:));
- (CGFloat)narrativesCollectionViewLayout:(UICollectionViewLayout*)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section
NS_SWIFT_NAME(narrativesCollectionViewLayout(_:minimumLineSpacingFor:));
@end

NS_SWIFT_NAME(NarrativesView)
@interface NFNarrativesView : UIView
    
@property (weak, nonatomic) id<NFNarrativesViewDelegate> delegate;
@property (weak, nonatomic) id<NFNarrativesViewCellDeleagate> cellDelegate;

@property (strong, nonatomic) NSString *serviceKey;
@property (nonatomic) BOOL sandBox;
@property (strong, nonatomic) NSString *uniqueKey;
@property (strong, nonatomic) NSArray <NSString *> *tags;

@property (nonatomic, readonly) BOOL isContent;

@property (strong, nonatomic) IBInspectable NSString *title;
@property (strong, nonatomic) IBInspectable UIColor *titleColor;
@property (strong, nonatomic) IBInspectable NSString *titleFontFamily;
@property (nonatomic) IBInspectable CGFloat titleFontSize;

@property (nonatomic) IBInspectable int startNarrativeID;

@property (nonatomic) IBInspectable BOOL showingCellTitle;
@property (nonatomic) IBInspectable BOOL showingCellSource;
@property (nonatomic) IBInspectable BOOL showStatusBar;
@property (nonatomic) IBInspectable BOOL swipeToClose;
@property (nonatomic) IBInspectable BOOL overScrollToClose;

@property (strong, nonatomic) IBInspectable UIColor *cellBorderColor;

@property (strong, nonatomic) IBInspectable NSString *cellFontFamily;
@property (nonatomic) IBInspectable CGFloat cellFontSize;
@property (strong, nonatomic) IBInspectable UIColor *cellTitleColor;

@property (strong, nonatomic) IBInspectable NSString *cellSourceFontFamily;
@property (nonatomic) IBInspectable CGFloat cellSourceFontSize;
@property (strong, nonatomic) IBInspectable UIColor *cellSourceTitleColor;

@property (nonatomic) IBInspectable CGFloat cellSpacing;

@property (strong, nonatomic) IBInspectable UIColor *containerBackgroundColor;
@property (strong, nonatomic) IBInspectable UIColor *listBackgroundColor;

@property (nonatomic, strong) IBInspectable UIColor *placeholderElementColor;
@property (nonatomic, strong) IBInspectable UIColor *placeholderBackgroundColor;

@property (nonatomic, strong, nullable) UIView<NFNarrativePlaceholderProtocol> *placeholderView;

@property (strong, nonatomic) UIImage *likeImage;
@property (strong, nonatomic) UIImage *likeSelectedImage;
@property (strong, nonatomic) UIImage *dislikeImage;
@property (strong, nonatomic) UIImage *dislikeSelectedImage;
@property (strong, nonatomic) UIImage *favoriteImage;
@property (strong, nonatomic) UIImage *favoriteSelectedImage;

@property (nonatomic) BOOL likePanel;
@property (nonatomic) BOOL favoritePanel;

@property (nonatomic) IBInspectable CGSize popupSize;

@property (assign, nonatomic) NFNarrativeCellStyle cellStyle;
@property (assign, nonatomic) NFNarrativeClosePosition closeButtonPosition;
@property (assign, nonatomic) NFNarrativeScrollStyle scrollNarrativeStyle;
@property (assign, nonatomic) NFNarrativePresentationStyle presentationStyle;

@property (nonatomic, readonly) NSString *frameworkInfo;

@property (weak, nonatomic) IBOutlet UIViewController *targetController;

- (void)registerNib:(nullable UINib *)nib forCellWithReuseIdentifier:(NSString *)identifier;
- (void)create;
- (void)showNarrativeWithID:(int)narrativeID;
- (void)showSingleNarrativeWithID:(int)narrativeID fromTarget:(UIViewController *)target;
- (void)closeNarrative;
- (void)refreshNarratives;
- (void)refreshCurrentNarrative;
- (void)visibleUpdate;
    
@end

NS_ASSUME_NONNULL_END
