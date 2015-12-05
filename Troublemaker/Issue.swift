//
//  Issue.swift
//  Troublemaker
//
//  Created by Andrei Raifura on 11/22/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

public enum Issue {
    case Warning(IssueData)
    case Error(IssueData)
    
    var data: IssueData {
        switch self {
        case .Warning(let data):
            return data
        case .Error(let data):
            return data
        }
    }
    
}


public extension Issue {
    init?(log: String) {
        guard let data = log.convert() else { return nil }
        let issueData = IssueData(logData: data)
        self = data.issueTypeString == warning ? Warning(issueData) : Error(issueData)
    }
    
}


extension Issue : Equatable {}

public func ==(lhs: Issue, rhs: Issue) -> Bool {
    switch (lhs, rhs) {
    case (let .Warning(lhsData), let .Warning(rhsData)):
        return lhsData == rhsData
    case (let .Error(lhsData), let .Error(rhsData)):
        return lhsData == rhsData
    default:
        return false
    }
    
}
