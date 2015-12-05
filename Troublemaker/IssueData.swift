//
//  IssueData.swift
//  Troublemaker
//
//  Created by Andrei Raifura on 11/22/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

public struct IssueData {
    
    public let title: String
    public let filePath: String?
    public let line: UInt?
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