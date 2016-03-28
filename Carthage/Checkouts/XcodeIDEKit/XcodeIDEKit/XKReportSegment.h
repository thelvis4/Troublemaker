//
//  XKReportSegment.h
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/15/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import <Foundation/Foundation.h>

@class IDEActivityReportStringSegment;

@interface XKReportSegment : NSObject

@property (nonnull, nonatomic, strong, readonly) IDEActivityReportStringSegment *IDEActivityReportStringSegment;

- (nonnull instancetype)initWithString:(nonnull NSString *)string
                             separator:(nullable NSString *)separator;

- (nonnull instancetype)initWithString:(nonnull NSString *)string
                        frontSeparator:(nullable NSString *)frontSeparator
                         backSeparator:(nullable NSString *)backSeparator;

- (nonnull instancetype)initWithDate:(nonnull NSDate *)date;

- (nonnull instancetype)initWithDate:(nonnull NSDate *)date
                           dateStyle:(NSDateFormatterStyle)dateStyle
                           timeStyle:(NSDateFormatterStyle)timeStyle;

- (nonnull instancetype)initWithDate:(nonnull NSDate *)date
    frontSeparator:(nullable NSString *)frontSeparator
     backSeparator:(nullable NSString *)backSeparator
         dateStyle:(NSDateFormatterStyle)dateStyle
         timeStyle:(NSDateFormatterStyle)timeStyle;

- (nonnull instancetype)initBoldSegmentWithString:(nonnull NSString *)string;

- (nonnull instancetype)initBoldSegmentWithString:(nonnull NSString *)string
                                   frontSeparator:(nullable NSString *)frontSeparator
                                    backSeparator:(nullable NSString *)backSeparator;
@end

