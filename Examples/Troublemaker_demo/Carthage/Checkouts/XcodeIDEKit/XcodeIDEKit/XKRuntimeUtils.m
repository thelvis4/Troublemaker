//
//  XKRuntimeUtils.m
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/11/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import "XKRuntimeUtils.h"
#import <objc/runtime.h>

id getPropertyWithNameFromObject(const char *propertyName, id containingObject) {
    Class class = [containingObject class];
    Ivar ivar = class_getInstanceVariable(class, propertyName);

    return object_getIvar(containingObject, ivar);
}