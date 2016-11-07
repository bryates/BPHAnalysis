import FWCore.ParameterSet.Config as cms

process = cms.Process("bphAnalysis")

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(True)

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring(
#
### use this to access the nearest copy of the input file, querying the catalog
    #'/store/mc/RunIISpring15DR74/BsToJpsiPhi_BMuonFilter_TuneCUEP8M1_13TeV-pythia8-evtgen/MINIAODSIM/Asympt25nsRaw_MCRUN2_74_V9-v1/50000/0E685515-8661-E511-8274-00259073E3B6.root'
    '/store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext3-v2/70000/00287FF4-0E40-E611-8D06-00266CFE78EC.root'
#
### use this to access the input file if by any reason you want to specify 
### the data server
#    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/BsToJpsiPhi_BMuonFilter_TuneCUEP8M1_13TeV-pythia8-evtgen/MINIAODSIM/Asympt25nsRaw_MCRUN2_74_V9-v1/50000/0E685515-8661-E511-8274-00259073E3B6.root'
#
### use this to access an input file locally available
#    'file:/...complete_file_path.../0E685515-8661-E511-8274-00259073E3B6.root'
))

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.testJPsiSpecificDecay = cms.EDAnalyzer('TestJPsiSpecificDecay',
    patMuonLabel = cms.string('slimmedMuons::PAT'),
    pcCandsLabel = cms.string('packedPFCandidates::PAT'),
    outDump = cms.string('dump_JPsi.txt'),
    #outHist = cms.string('hist_mini.root')
)

process.p = cms.Path(
    process.testJPsiSpecificDecay
)

