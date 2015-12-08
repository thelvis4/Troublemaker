//
//  Troublemaker.swift
//  Troublemaker
//
//  Created by Andrei Raifura on 11/22/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

import XcodeIDEKit

/**
 Defines a protocol for Issues controllers. This was mostly done to allow 
 mocking.
 */
public protocol IssueController {
    typealias IssueType
    
    func addIssue(issue: IssueType)
    func removeIssue(issue: IssueType)
    func clearAllIssues()
    func clearGeneratedIssues()
    
}

/**
 The responsible for injecting(adding) and removing Warning and Errors in Xcode.
 
 In this project `Warnings` and `Errors` are collectively called `Issues`.
 
 #### How it works
 It starts being initialized with an instance of type NSWindowController.
 It fails if the instance passed as parameter is not an
 `IDEWorkspaceWindowController` (private class) object.
 
 This happens because `Troublemaker` can only work if it gets access to Xcode's
 window controller.
 
 An instance of NSWindowController can be usually obtained by calling:
 ```
 NSApp.keyWindow?.windowController
 ```
 #### Important
 This project is usseful only if the caller can get access to Xcode's window
 controller. The only known way to do this is from a Xcode plugin.
 */
public struct Troublemaker: IssueController {
    
    let windowController: XKWorkspaceWindowController
    
    /**
     Initializes a instance of `Troublemaker` with a `NSWindowController`.
     
     - parameter windowController: An instance of type `NSWindowController`.
                                   It must be Xcode's window controller.
     
     - returns: An instance of Troublemaker if the object passed as parameter
                is Xcode's NSWindowController. Otherwise, it fails returning
                `nil`.
     */
    public init?(windowController: NSWindowController) {
        if let workspaceController = XKWorkspaceWindowController(NSWindowController: windowController) {
            self.windowController = workspaceController
        } else {
            return nil
        }
    }
    
    /**
     Initializes a instance of `Troublemaker`. It will try to gather an instance
     of `NSWindowController` automatically.
     
     - returns: An instance of Troublemaker if the gathered `NSWindowController`
                is Xcode's NSWindowController. Otherwise, it fails returning
                `nil`.
     */
    public init?() {
        if let windowController = NSApp.keyWindow?.windowController {
            self.init(windowController: windowController)
        } else {
            return nil
        }
    }
    
    /**
     Injects an issue in Xcode.
     
     - parameter issue: An `Issue` type.
     */
    public func addIssue(issue: Issue) {
        windowController.issueManger.addIssue(issue.IDEKitIssue)
    }
    
    /**
     Removes a specific issue from Xcode if there is an issue that matches the
     info from the `Issue` instance passed as parameter. Otherwise, nothing happens.
     
     - parameter issue: An `Issue` type.
     */
    public func removeIssue(issue: Issue) {
        windowController.issueManger.removeIssue(issue.IDEKitIssue)
    }
    
    /**
     Removes all the issues from Xcode, no matter if there are warnings, errors,
     user-generated or Xcode generated. It removes all of them.
     */
    public func clearAllIssues() {
        windowController.issueManger.clearAllIssues()
    }
    
    /**
     Removes generated(using this framework) issues from Xcode.
     */
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
