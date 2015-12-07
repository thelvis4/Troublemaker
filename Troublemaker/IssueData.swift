//
//  IssueData.swift
//  Troublemaker
//
//  Created by Andrei Raifura on 11/22/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

/**
Contains the data needed to describe a Xcode issue.
*/
public struct IssueData {
    /// The message that will be displayed in Xcode.
    public let title: String
    /// The path to a file the issue will referr to.
    public let filePath: String?
    /// The line number in file located at `filePath` the issue will reffer to.
    public let line: UInt?
    /// The characted number of the `line` in file located at `filePath` the
    /// issue will reffer to.
    public let column: UInt?
    
    public init(title: String, filePath: String? = nil) {
        self.title = title
        self.filePath = filePath
        self.line = nil
        self.column = nil
    }
    
    public init(title: String, filePath: String, line: UInt, column: UInt? = nil) {
        self.title = title
        self.filePath = filePath
        self.line = line
        self.column = column
    }
    
}


internal extension IssueData {
    
    internal init(logData: IssueLogData) {
        title = logData.title
        let location = logData.location
        filePath = location?.filePath
        line = location?.line
        column = location?.column
    }
    
}


extension IssueData : Equatable {}

public func ==(lhs: IssueData, rhs: IssueData) -> Bool {
    return lhs.title == rhs.title &&
        lhs.filePath == rhs.filePath &&
        lhs.line == rhs.line &&
        lhs.column == rhs.column
}