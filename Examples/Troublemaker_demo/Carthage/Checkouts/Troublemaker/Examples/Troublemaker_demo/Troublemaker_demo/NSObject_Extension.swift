//
//  NSObject_Extension.swift
//
//  Created by Andrei Raifura on 12/7/15.
//  Copyright © 2015 YOPESO. All rights reserved.
//

import Foundation

extension NSObject {
    class func pluginDidLoad(bundle: NSBundle) {
        let appName = NSBundle.mainBundle().infoDictionary?["CFBundleName"] as? NSString
        if appName == "Xcode" {
        	if sharedPlugin == nil {
        		sharedPlugin = Troublemaker_demo(bundle: bundle)
        	}
        }
    }
}