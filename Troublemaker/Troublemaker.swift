//
//  Troublemaker.swift
//  Troublemaker
//
//  Created by Andrei Raifura on 11/22/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

import XcodeIDEKit

public struct Troublemaker {
    
    let windowController: XKWorkspaceWindowController
    
    public init?(windowController: NSWindowController) {
        if let workspaceController = XKWorkspaceWindowController(NSWindowController: windowController) {
            self.windowController = workspaceController
        } else {
            return nil
        }
    }
    
    public init?() {
        if let windowController = NSApp.keyWindow?.windowController {
            self.init(windowController: windowController)
        } else {
            return nil
        }
    }
    
    public func addIssue(issue: Issue) {
        windowController.issueManger.addIssue(issue.IDEKitIssue)
    }
    
    public func removeIssue(issue: Issue) {
        windowController.issueManger.removeIssue(issue.IDEKitIssue)
    }
    
    public func clearAllIssues() {
        windowController.issueManger.clearAllIssues()
    }
    
    public func clearGeneratedIssues() {
        windowController.issueManger.clearGeneratedIssues()
    }
    
}



internal extension Issue {
    internal var IDEKitIssue: XKIssue {
        switch (data.filePath, data.line) {
        case (let filePath?, nil):
            return XKIssue(title: data.title, filePath: filePath, severity: issueSeverity)
        case (let filePath?, let line?):
            return XKIssue(title: data.title, filePath: filePath, lineNumber: line, severity: issueSeverity)
        default:
            return XKIssue(title: data.title, severity: issueSeverity)
        }
    }
    
    private var issueSeverity: XKIssueSeverity {
        switch self {
        case .Warning(_):
            return XKIssueSeverity.Issue
        case .Error(_):
            return XKIssueSeverity.Error
        }
    }
}