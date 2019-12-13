//
//  NFFavoriteNarrativesView.h
//  NarrativesFramework
//
//  Created by StPashik on 22/11/2019.
//  Copyright © 2019 kiozk. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NFNarrativesView.h"

NS_ASSUME_NONNULL_BEGIN

@class NFFavoriteNarrativesView;

NS_SWIFT_NAME(FavoriteNarrativesViewDelegate)
/**
 Протокол делегата для отслеживания действий NarrativesView
 */
@protocol NFFavoriteNarrativesViewDelegate <NSObject>
@optional
/**
 Отслеживание обновления нарративов внутри FavoriteNarrativesView

 @param favoriteNarrativeView NarrativesView
 */
- (void)favoriteNarrativeViewUpdated:(NFFavoriteNarrativesView *)favoriteNarrativeView;

/**
 Обработка нажатия на кнопку внутри карточки нарратива

 @param favoriteNarrativeView FavoriteNarrativesView
 @param target сстылка переданная от кнопки внутри карточки
 */
- (void)favoriteNarrativeView:(NFFavoriteNarrativesView *)favoriteNarrativeView getLinkWithTarget:(NSString *)target;

/**
 Отслеживание закрытия ридера нарративов
 */
- (void)favoriteNarativeReaderDidClose;
@end

NS_SWIFT_NAME(FavoriteNarrativesView)
@interface NFFavoriteNarrativesView : UIView

@property (weak, nonatomic) id<NFFavoriteNarrativesViewDelegate> delegate;
@property (weak, nonatomic) id<NFNarrativesViewCellDeleagate> cellDelegate;

@property (nonatomic) IBInspectable BOOL showingCellTitle;
@property (nonatomic) IBInspectable BOOL showingCellSource;
@property (nonatomic) IBInspectable BOOL showStatusBar;
@property (nonatomic) IBInspectable BOOL swipeToClose;
@property (nonatomic) IBInspectable BOOL overScrollToClose;

@property (strong, nonatomic) UIFont *cellTitleFont;
@property (strong, nonatomic) IBInspectable UIColor *cellBorderColor;

@property (strong, nonatomic) IBInspectable NSString *cellFontFamily;
@property (nonatomic) IBInspectable CGFloat cellFontSize;
@property (strong, nonatomic) IBInspectable UIColor *cellTitleColor;

@property (strong, nonatomic) IBInspectable NSString *cellSourceFontFamily;
@property (nonatomic) IBInspectable CGFloat cellSourceFontSize;
@property (strong, nonatomic) IBInspectable UIColor *cellSourceTitleColor;

@property (nonatomic) IBInspectable CGFloat cellSpacing;

@property (nonatomic) IBInspectable CGSize popupSize;

@property (nonatomic, strong) IBInspectable UIColor *placeholderElementColor;
@property (nonatomic, strong) IBInspectable UIColor *placeholderBackgroundColor;

@property (assign, nonatomic) NFNarrativeCellStyle cellStyle;
@property (assign, nonatomic) NFNarrativeClosePosition closeButtonPosition;
@property (assign, nonatomic) NFNarrativeScrollStyle scrollNarrativeStyle;
@property (assign, nonatomic) NFNarrativePresentationStyle presentationStyle;

@property (nonatomic, strong, nullable) UIView<NFNarrativePlaceholderProtocol> *placeholderView;

@property (strong, nonatomic) UIImage *likeImage;
@property (strong, nonatomic) UIImage *likeSelectedImage;
@property (strong, nonatomic) UIImage *dislikeImage;
@property (strong, nonatomic) UIImage *dislikeSelectedImage;
@property (strong, nonatomic) UIImage *favoriteImage;
@property (strong, nonatomic) UIImage *favoriteSelectedImage;

@property (nonatomic) BOOL likePanel;
@property (nonatomic) BOOL favoritePanel;

@property (weak, nonatomic) IBOutlet UIViewController *targetController;

- (void)registerNib:(nullable UINib *)nib forCellWithReuseIdentifier:(NSString *)identifier;
- (void)create;
- (void)closeNarrative;
- (void)refreshCurrentNarrative;

@end

NS_ASSUME_NONNULL_END
