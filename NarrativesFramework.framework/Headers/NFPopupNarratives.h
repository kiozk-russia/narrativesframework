//
//  NFPopupNarratives.h
//  NarrativesFramework
//
//  Created by StPashik on 10/09/2019.
//  Copyright © 2019 kiozk. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NFNarrativesView.h"

NS_ASSUME_NONNULL_BEGIN

@class NFPopupNarratives;

NS_SWIFT_NAME(PopupNarrativesDelegate)
/**
 Протокол делегата для отслеживания действий NarrativesView
 */
@protocol NFPopupNarrativesDelegate <NSObject>
@optional
/**
 Отслеживание обновления нарративов внутри NarrativesView
 
 @param popupNarratives NFPopupNarratives
 */
- (void)popupNarrativesUpdated:(NFPopupNarratives *)popupNarratives;

/**
 Обработка нажатия на кнопку внутри карточки нарратива
 
 @param popupNarratives NFPopupNarratives
 @param target сстылка переданная от кнопки внутри карточки
 */
- (void)popupNarratives:(NFPopupNarratives *)popupNarratives getLinkWithTarget:(NSString *)target;

/**
 Отслеживание закрытия ридера нарративов
 */
- (void)popupNarativeReaderDidClose;
@end

NS_SWIFT_NAME(PopupNarratives)
@interface NFPopupNarratives : NSObject

@property (weak, nonatomic) id<NFPopupNarrativesDelegate> delegate;

@property (strong, nonatomic) NSString *uniqueKey;
@property (strong, nonatomic) NSArray <NSString *> *tags;

@property (nonatomic, readonly) BOOL isContent;

@property (nonatomic) IBInspectable BOOL showStatusBar;
@property (nonatomic) IBInspectable BOOL swipeToClose;
@property (nonatomic) IBInspectable BOOL overScrollToClose;

@property (nonatomic, strong) IBInspectable UIColor *placeholderElementColor;
@property (nonatomic, strong) IBInspectable UIColor *placeholderBackgroundColor;

@property (nonatomic) IBInspectable CGSize popupSize;

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

@property (nonatomic, readonly) NSString *frameworkInfo;

- (void)create;
- (void)closeNarrative;
- (void)refreshCurrentNarrative;

- (void)showNarrativesFrom:(UIViewController *)targetController;

@end

NS_ASSUME_NONNULL_END
