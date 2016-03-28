//
//  XKReportStringSegment.m
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/15/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import "XKReportSegment.h"
#import "XcodePrivate.h"

@interface XKReportSegment ()
@property (nonnull, nonatomic, strong, readwrite) IDEActivityReportStringSegment *IDEActivityReportStringSegment;
@end

@implementation XKReportSegment

- (instancetype)initWithString:(NSString *)string
                frontSeparator:(NSString *)frontSeparator
                 backSeparator:(NSString *)backSeparator {
    self = [super init];
    if (self) {
        _IDEActivityReportStringSegment = [[IDEActivityReportStringSegment alloc] initWithString:string
                                                                                        priority:1
                                                                                  frontSeparator:frontSeparator
                                                                                   backSeparator:backSeparator];
    }
    
    return self;
}


- (instancetype)initWithString:(NSString *)string separator:(NSString *)separator {
    return [self initWithString:string frontSeparator:nil backSeparator:separator];
}


- (instancetype)initWithDate:(NSDate *)date
              frontSeparator:(NSString *)frontSeparator
               backSeparator:(NSString *)backSeparator
                   dateStyle:(NSDateFormatterStyle)dateStyle
                   timeStyle:(NSDateFormatterStyle)timeStyle {
    self = [super init];
    if (self) {
        _IDEActivityReportStringSegment = [[IDEActivityReportDateStringSegment alloc] initWithDate:date
                                                                                          priority:1
                                                                                    frontSeparator:frontSeparator
                                                                                     backSeparator:backSeparator
                                                                                         dateStyle:dateStyle
                                                                                         timeStyle:timeStyle];
    }
    
    return self;
}


- (instancetype)initWithDate:(NSDate *)date
                   dateStyle:(NSDateFormatterStyle)dateStyle
                   timeStyle:(NSDateFormatterStyle)timeStyle {
    return [self initWithDate:date
               frontSeparator:nil
                backSeparator:nil
                    dateStyle:dateStyle
                    timeStyle:timeStyle];
    
}


- (instancetype)initWithDate:(NSDate *)date {
    return [self initWithDate:date
               frontSeparator:nil
                backSeparator:nil
                    dateStyle:NSDateFormatterShortStyle
                    timeStyle:NSDateFormatterShortStyle];
    
}


- (nonnull instancetype)initBoldSegmentWithString:(nonnull NSString *)string
                                   frontSeparator:(nullable NSString *)frontSeparator
                                    backSeparator:(nullable NSString *)backSeparator {
    self = [super init];
    if (self) {
        NSDictionary *attributes = @{NSForegroundColorAttributeName : [NSColor colorWithCalibratedWhite:0 alpha:1], NSFontAttributeName : [NSFont boldSystemFontOfSize:11.0]};
        NSAttributedString *attributedString = [[NSAttributedString alloc] initWithString:string attributes:attributes];
        
        _IDEActivityReportStringSegment = [[IDEActivityReportStringSegment alloc] initWithString:attributedString
                                                                                        priority:1
                                                                                  frontSeparator:frontSeparator
                                                                                   backSeparator:backSeparator];
    }
    
    return self;
}


- (instancetype)initBoldSegmentWithString:(NSString *)string {
    return [self initBoldSegmentWithString:string frontSeparator:nil backSeparator:nil];
}

@end
