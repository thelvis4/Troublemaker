//
//  Troublemaker_demo.swift
//
//  Created by Andrei Raifura on 12/7/15.
//  Copyright © 2015 YOPESO. All rights reserved.
//

import AppKit
import Troublemaker

var sharedPlugin: Troublemaker_demo?

class Troublemaker_demo: NSObject {
    
    var bundle: NSBundle
    lazy var center = NSNotificationCenter.defaultCenter()
    
    init(bundle: NSBundle) {
        self.bundle = bundle
        
        super.init()
        center.addObserver(self, selector: #selector(Troublemaker_demo.createMenuItems), name: NSApplicationDidFinishLaunchingNotification, object: nil)
    }
    
    deinit {
        removeObserver()
    }
    
    func removeObserver() {
        center.removeObserver(self)
    }
    
    func createMenuItems() {
        removeObserver()
        
        let item = NSApp.mainMenu!.itemWithTitle("Edit")
        if item != nil {
            let actionMenuItem = NSMenuItem(title:"Do Action", action:#selector(Troublemaker_demo.doMenuAction), keyEquivalent:"")
            actionMenuItem.target = self
            item!.submenu!.addItem(NSMenuItem.separatorItem())
            item!.submenu!.addItem(actionMenuItem)
        }
    }
    
    func doMenuAction() {
        guard let troublemaker = Troublemaker() else {
            print("Could not initialize Troublemaker.")
            return
        }
        
        // Clear all previously generated issues
        troublemaker.clearGeneratedIssues()
        
        // Create new issues
        if let logIssue = Issue(log: "warning: Hello Troublemakers!") {
            troublemaker.addIssue(logIssue)
        }
        
        let issueData = IssueData(title: "Hey hey!")
        let warning = Issue.Warning(issueData)
        troublemaker.addIssue(warning)

        let error = Issue.Error(issueData)
        troublemaker.addIssue(error)
    }
    
}

